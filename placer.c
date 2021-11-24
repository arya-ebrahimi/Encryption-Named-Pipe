#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    
    const char *pipe_bc = "/tmp/pipe_bc";
    mkfifo(pipe_bc, 0666);

    int fd = open(pipe_bc, O_RDONLY);
    char str[100];
    read(fd, str, 100);
    const char *pipe_c = "/tmp/pipe_c";
    mkfifo(pipe_c, 0666);

    int fd2 = open(pipe_c, O_RDONLY);
    char str2[100];
    read(fd2, str2, 100);

    char result[200] = "";

    int j = 0;
    int k = 0;
    for (int i = 0; i < strlen(str2); i++) {
        if (str2[i] == '$') {
            while (str[k] != ' ') {
                result[j++] = str[k++];
            }
            k++;
            
        } else {
            result[j++] = str2[i];
        }
    }

    FILE *f = fopen("files/placer.txt", "w+");
    fputs(result, f);
    fclose(f);

    close(fd);
    close(fd2);

    return 0;



}