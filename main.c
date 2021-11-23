#include <stdio.h>
#include <string.h>
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
    // process_c = fork();

    if (process_a == 0) {
        //child a (decoder)
        char * argv_list[2] = {"./build/decoder", NULL};
        execv(argv_list[0], argv_list);
        
    } else if (process_b == 0) {
        //child b (finder)
        char * argv_list[2] = {"./build/finder", NULL};
        execv(argv_list[0], argv_list);

    // } else if (process_c == 0) {
    //     //child c (placer)
    } else {
        //parent
        char * pipe_a = "/tmp/pipe_a";
        mkfifo(pipe_a, 0777);
        int fd = open(pipe_a, O_WRONLY);
        char *ptr = "decoderdecoderdecoderdecoder";
        write(fd, ptr, strlen(ptr)+1);
        close(fd);
        waitpid(process_a, &status, 0);

        char * pipe_b = "/tmp/pipe_b";
        mkfifo(pipe_b, 0777);
        int fd2 = open(pipe_b, O_WRONLY);
        char *ptr2 = "0 2$3 5";
        write(fd2, ptr2, strlen(ptr2)+1);
        close(fd2);

        waitpid(process_b, &status, 0);


        // waitpid(process_c, &status, 0);


        // char * pipe_b = "/tmp/pipe_b";
        // mkfifo(pipe_b, 0777);
        // fd = open(pipe_b, O_WRONLY);
        // char *ptr2 = "0 2$4 4$";
        // write(fd, ptr2, strlen(ptr2)+1);
        // close(fd);
        return 0;

        
    }

}
