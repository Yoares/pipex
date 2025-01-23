#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h> 
#include <fcntl.h>

int main(int ac, char *av[])
{
    int n;

    int fd = open("fd.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    int fd1 = open("fd1.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);

    if (fd == -1 || fd1 == -1)
    {
        perror("error");
        return 1;
    }

    int id = fork();
    if (id == 0)  // child process l3ar
    {
        n = 1;
        int i = n;
        while (i < n + 5)
        {
            char c = i + '0';
            write(fd, &c , 1);
            i++;      
        }
    }
    else  {
        n = 5;
        wait(NULL);
        int i = n;
        while (i < n + 5)
        {
            char c = i + '0';
            write(fd1, &c, 1);
            i++;      
        }     
    }
    printf("\n");
}