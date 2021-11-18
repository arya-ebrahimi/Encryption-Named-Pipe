#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {
        const char *pipe_file = "/tmp/decoder_pipe";
        //child process (decoder)
        mkfifo(pipe_file, 0666);
        int fd = open(pipe_file, O_WRONLY);
        char *ptr = "decoderrr";
        write(fd, ptr, strlen(ptr)+1);
    
        char * argv_list[2] = {"./decoder", NULL};
        execv(argv_list[0], argv_list);
        
    } else {
        // pid_t pid2 = fork();

        // if (pid2 == 0) {
        //     //child process (finder)
        //     char * argv_list[] = {"./finder", NULL};
        //     execv(argv_list[0], argv_list);
        // }

        // else {
        //     pid_t pid3 = fork();

        //     if (pid3 == 0) {
        //         //child process (placer)
        //         char * argv_list[] = {"./placer", NULL};
        //         execv(argv_list[0], argv_list);
        //     }
        
        // }
        // printf("child");
        
    }

}
