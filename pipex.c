#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h> 
#include <fcntl.h>

/*
    -create process to handle 1st cmd
    - parse cmd :
        - chekc if cmd is valid 
        -run command
*/

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void    error_message(const char *msg)
{
    write(STDERR_FILENO, msg, ft_strlen(msg));
}

int main(int ac, char *av[], char **envp)
{
    if (ac != 4)
    {
        error_message("Usage: ./pipex <input_file> <output_file> <command>\n");
        return 1;
    }

    int in_fd = open(av[1], O_CREAT | O_RDONLY | O_TRUNC, 0664);
    if (in_fd == -1)
    {
        error_message("Error: Unable to open intput file\n");
        return 1;
    }

    int out_fd = open(av[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
    if (out_fd == -1)
    {
        error_message("Error: Unable to open output file\n");
        close(in_fd);
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror ("pipe error");
        close(in_fd);
        close(out_fd);
        return 1;
    }

    int pid = fork();
    if (pid == -1)
    {
        perror ("errorfork");
        close(in_fd);
        close(out_fd);
        return 1;
    }
    else if (pid == 0)  // child process l3ar
    {
        {
            // Redirect input to stdin
            if (dup2(in_fd, STDIN_FILENO) == -1)
            {
                error_message("Error: Failed to redirect stdin\n");
                exit(1);
            }
            close(in_fd);

            // Redirect stdout to output file
            if (dup2(out_fd, STDOUT_FILENO) == -1)
            {
                error_message("Error: Failed to redirect stdout\n");
                exit(1);
            }
            close(out_fd);

            char *cmd_args[] = {av[3], NULL};
            if (execve(cmd_args[0], cmd_args, envp) == -1)
            {
                error_message("Error: Command execution failed\n");
                exit(1);
            }
            else
            {

                close(in_fd);
                close(out_fd);

                wait(NULL);
            }

            return 0;
        }
    }
}