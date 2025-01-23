#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h> 

int main(int ac, char *av[])
{
    int n;

    int id = fork();
    if (id == 0)
    {
        n = 1;
    }
    else  {
        id = 0;        
    }
    // if (id != 0)
    // {
    //     wait(&id);
    // }
    
    int i = n;
    while (i < n + 5)
    {
        printf("%d", i);
        fflush(stdout);  
        i++;      
    }
    printf("\n");
}