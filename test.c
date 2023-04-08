#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1
#define PATH "/bin/"

extern char **environ;

void	run(char *command, char **args, int *inpipe, int *outpipe)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("fork()");
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
	{
		puts(command);
		if (inpipe)
		{
			close(inpipe[WRITE_END]);
			dup2(inpipe[READ_END], STDIN_FILENO);
			close(inpipe[READ_END]);
		}
		if (outpipe)
		{
			close(outpipe[READ_END]);
			dup2(outpipe[WRITE_END], STDOUT_FILENO);
			close(outpipe[WRITE_END]);
		}
		execve(command, args, environ);
	}
}

int main (int argc, char **argv) {
    int		i;
	char	*args[2] = {0};

    for(i = 1; i < argc - 1; i++)
    {
        int pd[2];
        pipe(pd);

        if (!fork()) {
            dup2(pd[WRITE_END], STDOUT_FILENO); // remap output back to parent
			args[0] = argv[i];
			execve(argv[i], args, environ);
		}
        // remap output from previous child to input
        dup2(pd[READ_END], STDIN_FILENO);
        close(pd[WRITE_END]);
    }
	args[0] = argv[i];
	execve(argv[i], args, environ);
}
