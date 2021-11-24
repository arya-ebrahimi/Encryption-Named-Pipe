#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>  


int main() {

    const char *pipe_file2 = "/tmp/pipe_ab";
    int fd2 = open(pipe_file2, O_RDONLY);
    char str[100];
    read(fd2, str, 100);
    close(fd2);

    const char *pipe_file = "/tmp/pipe_b";
    int fd = open(pipe_file, O_RDONLY);
    char str2[100];
    read(fd, str2, 100);
    close(fd);
    char *token = strtok(str2, "$");
    char result[200] = "";

    FILE *f = fopen("files/result.txt", "w+");

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

        printf("%d %d\n", num1, num2);
        
        for (int i = num1; i < num1+num2; i++) {
            result[j++] = str[i];
        }
        result[j++] = ' ';
        token = strtok(NULL, "$");
    }

    fputs(result, f);
    fclose(f);

    char * pipe_bc = "/tmp/pipe_bc";
    mkfifo(pipe_bc, 0777);
    int fd3 = open(pipe_bc, O_WRONLY);
    write(fd3, result, strlen(result)+1);
    close(fd3);

    return 0;

}



