#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

int main(void)
{
    int fd[2];
    pid_t pid;

    printf("This is the parent pid: %d\n", getpid());
    if (pipe(fd) < 0)
    {
        perror("pipe():");
        return EXIT_FAILURE;
    }
    pid = fork();
    if (pid < 0)
    {
        perror("pid():");
        return EXIT_FAILURE;
    }
    /* Parent */
    else if (pid > 0)
    {
        close(fd[READ_END]);
        write(fd[WRITE_END], "HELLO", 5);
        close(fd[WRITE_END]);

        waitpid(pid, NULL, 0);
        char buf[200] = {0};

        close(fd[WRITE_END]);
        read(fd[READ_END], buf, 200);
        printf("Received from child: %s\n", buf);
        close(fd[READ_END]);
    }
    /* Child */
    else
    {
        printf("This is the childs pid: %d\n", getpid());
        char buf[200] = {0};

        close(fd[WRITE_END]);
        read(fd[READ_END], buf, 200);
        printf("Received from parent: %s\n", buf);

        close(fd[READ_END]);
        write(fd[WRITE_END], "WORLD!", 6);
        close(fd[WRITE_END]);
    }
    return 0;
}
