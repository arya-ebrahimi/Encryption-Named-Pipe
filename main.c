#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main() {

    pid_t process_a;
    pid_t process_b;
    pid_t process_c;

    int status;

    process_a = fork();
    process_b = fork();
    process_c = fork();

    if (process_a == 0) {
        //child a (decoder)
        char * argv_list[2] = {"./build/decoder", NULL};
        execv(argv_list[0], argv_list);
        
    } else if (process_b == 0) {
        //child b (finder)
        char * argv_list[2] = {"./build/finder", NULL};
        execv(argv_list[0], argv_list);

    } else if (process_c == 0) {
        //child c (placer)
        char * argv_list[2] = {"./build/placer", NULL};
        execv(argv_list[0], argv_list);
    } else {
        //parent

        FILE *input = fopen("files/input.txt", "rb");
        char *input_str;
        if (input) {
            fseek(input, 0, SEEK_END);
            long length = ftell(input);
            fseek(input, 0, SEEK_SET);
            input_str = malloc (length);
            if (input_str) {
                fread(input_str, 1, length, input);
            }
            fclose(input);
        }

        char *token = strtok(input_str, "###");
        char *ptr;
        char *ptr2;
        char *ptr3;
        int counter = 0;
        while (token != NULL)
        {
            switch (counter) {
            case 0:
                ptr = malloc (strlen(token));
                strcpy(ptr, token);
                break;
            case 1:
                ptr2 = malloc (strlen(token));
                strcpy(ptr2, token);
                break;
            case 2:
                ptr3 = malloc (strlen(token));
                strcpy(ptr3, token);
                break;
            
            default:
                break;
            }

            counter++;
            token = strtok(NULL, "###");
        }

        char * pipe_a = "/tmp/pipe_a";
        mkfifo(pipe_a, 0666);
        int fd = open(pipe_a, O_WRONLY);
        write(fd, ptr, strlen(ptr)+1);
        close(fd);

        waitpid(process_a, &status, 0);

        FILE *output = fopen("files/output.txt", "w+");
        
        fputs(ptr2, output);
        fclose(output);
        char *pipe_b = "/tmp/pipe_b";
        mkfifo(pipe_b, 0666);
        int fd2 = open(pipe_b, O_WRONLY);
        write(fd2, ptr2, strlen(ptr2)+1);
        close(fd2);

        waitpid(process_b, &status, 0);


        char *pipe_c = "/tmp/pipe_c";
        mkfifo(pipe_c, 0666);
        int fd3 = open(pipe_c, O_WRONLY);
        write(fd3, ptr3, strlen(ptr3)+1);
        close(fd3);

        waitpid(process_c, &status, 0);

        return 0;

        
    }

}
