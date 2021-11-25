#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 100


int main() {
    
    const char *pipe_bc = "/tmp/pipe_bc";
    mkfifo(pipe_bc, 0666);

    int fd = open(pipe_bc, O_RDONLY);
    char decoded_words[SIZE];
    read(fd, decoded_words, SIZE);
    const char *pipe_c = "/tmp/pipe_c";
    mkfifo(pipe_c, 0666);

    int fd2 = open(pipe_c, O_RDONLY);
    char main_text[SIZE];
    read(fd2, main_text, SIZE);

    char result[2*SIZE];

    int j = 0;
    int k = 0;
    for (int i = 1; i < strlen(main_text); i++) {
        if (main_text[i] == '$') {
            while (decoded_words[k] != ' ') {
                result[j++] = decoded_words[k++];
            }
            k++;
            
        } else {
            result[j++] = main_text[i];
        }
    }

    FILE *f = fopen("files/placer.txt", "w+");
    fputs(result, f);

    mkfifo(pipe_c, 0666);
    int fd3 = open(pipe_c, O_WRONLY);
    write(fd3, result, strlen(result)+1);
    close(fd3);


    fclose(f);
    close(fd);
    close(fd2);

    return 0;



}