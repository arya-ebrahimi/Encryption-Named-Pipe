#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
    
    const char *pipe_file = "/tmp/pipe_a";
    int fd = open(pipe_file, O_RDONLY);
    char str[100];

    read(fd, str, 100);
    close(fd);

    for (int i = 0; i<strlen(str); i++) {
        if ((str[i] > 67 && str[i] < 91) || ((str[i] > 99 && str[i] < 123))) {
           str[i] = str[i]-3;
        } else if ((str[i] < 68 && str[i] > 64) || (str[i] < 100 && str[i] > 96)) {
           str[i] = str[i]+23;
        }
    }

    FILE *f;
    f = fopen("files/file_decoder.txt", "w+");
    fputs(str, f);
    fclose(f);
    mkfifo("/tmp/pipe_ab", 0777);
    fd = open("/tmp/pipe_ab", O_WRONLY);
    write(fd, str, strlen(str)+1);
    close(fd);

    return 0;
}
