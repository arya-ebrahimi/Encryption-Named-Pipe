#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
    
    const char *pipe_file = "/tmp/decoder_pipe";
    int fd = open(pipe_file, O_RDONLY);
    char str[100];

    read(fd, str, 100);

    for (int i = 0; i<strlen(str); i++) {
        if ((str[i] > 67 && str[i] < 91) || ((str[i] > 99 && str[i] < 123))) {
           str[i] = str[i]-3;
        } else if ((str[i] < 68 && str[i] > 64) || (str[i] < 100 && str[i] > 96)) {
           str[i] = str[i]+23;
        }

    }

    FILE *f;
    f = fopen("file_decoder.txt", "w+");
    fputs(str, f);
    fclose(f);
    close(fd);

}
