#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>  


int main() {

    char index[100];
    char decoded[100];

    const char *pipe_ab = "/tmp/pipe_ab";
    const char *pipe_b = "/tmp/pipe_b";
    mkfifo(pipe_b, 0666);
    mkfifo(pipe_ab, 0666);

    char result[200] = "";
    int fd2, fd;

    fd2 = open(pipe_ab, O_RDONLY);
    read(fd2, decoded, 100);

    fd = open(pipe_b, O_RDONLY);
    read(fd, index, 100);
    char *token = strtok(index, "$");
    
    int j = 0;
    while (token != NULL)
    {
        int l = 0;
        while (token[l] != ' ') {
            l++;
        }

        char n1[8], n2[8];

        for (int i = 0; i < l; i++) {
            n1[i] = token[i];
        }

        int k = 0;
        for (int i = l+1; i < strlen(token); i++) {
            n2[k++] = token[i];
        }
        int num1 = atoi(n1);
        int num2 = atoi(n2);
        
        for (int i = num1; i < num1+num2; i++) {
            result[j++] = decoded[i];
        }
        result[j++] = ' ';
        token = strtok(NULL, "$");
    }   

    FILE *f = fopen("files/result.txt", "w+");
    fputs(result, f);
    fclose(f);

    char * pipe_bc = "/tmp/pipe_bc";
    mkfifo(pipe_bc, 0666);
    int fd3 = open(pipe_bc, O_WRONLY);
    write(fd3, result, strlen(result)+1);

    // close(fd3);
    close(fd2);
    close(fd);

    return 0;

}



