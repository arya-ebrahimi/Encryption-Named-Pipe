#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZE 100


int main() {
    
    const char *pipe_file = "/tmp/pipe_a";
    mkfifo(pipe_file, 0666);

    int fd = open(pipe_file, O_RDONLY);
    char str[SIZE];

    read(fd, str, SIZE);
    char result[2*SIZE] = "";
    int j = 0;

    for (int i = 0; i<strlen(str); i++) {

        if(str[i] == '\n' || str[i] == ' ') {
            continue;
        }

        if ((str[i] > 67 && str[i] < 91) || ((str[i] > 99 && str[i] < 123))) {
           result[j++] = str[i]-3;
        } else if ((str[i] < 68 && str[i] > 64) || (str[i] < 100 && str[i] > 96)) {
           result[j++] = str[i]+23;
        } else {
            continue;
        }
    }

    FILE *f;
    f = fopen("files/file_decoder.txt", "w+");
    fputs(result, f);
    fclose(f);
    mkfifo("/tmp/pipe_ab", 0666);
    int fd2 = open("/tmp/pipe_ab", O_WRONLY);
    write(fd2, result, strlen(str)+1);

    close(fd);
    close(fd2);


    return 0;
}
