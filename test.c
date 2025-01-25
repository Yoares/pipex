#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h> 
#include <fcntl.h>

int main(int ac, char *av[])
{
    int n;

    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror ("pipeerror");
        return 1;
    }

    int id = fork();
    if (id == -1)
    {
        perror ("errorfork");
        return 1;
    }

    if (id == 0)  // child process l3ar
    {
        close(pipefd[0]); // Close lkhra
        n = 1;
        int i = n;
        while (i < n + 5)
        {
            char c = i + '0';
            write(pipefd[1], &c , 1);
            i++;      
        }
        close(pipefd[1]);
    }
    else  {
        close(pipefd[1]); // Close type shit
        wait(NULL);

        char buffer[1];
        while (read(pipefd[0], buffer, sizeof(char)) > 0)
        {
            write(STDOUT_FILENO, buffer, 1);
        }
        close(pipefd[0]);
        printf("\n");
    }

}