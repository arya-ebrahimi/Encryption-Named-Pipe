#include <stdio.h>

int main() {

    const char *pipe_bc = "/tmp/pipe_bc";
    int fd = open(pipe_bc, O_RDONLY);
    char str2[100];
    read(fd, str2, 100);
    close(fd);

}