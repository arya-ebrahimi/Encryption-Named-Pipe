#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    const char *pipe_bc = "/tmp/pipe_bc";
    int fd = open(pipe_bc, O_RDONLY);
    char str[100];
    read(fd, str, 100);
    close(fd);
    const char *pipe_file2 = "/tmp/pipe_c";
    int fd2 = open(pipe_file2, O_RDONLY);
    char str2[100];
    read(fd2, str2, 100);
    close(fd2);

    FILE *f = fopen("files/placer.txt", "w+");
    fputs(str, f);
    fclose(f);

    return 0;



}