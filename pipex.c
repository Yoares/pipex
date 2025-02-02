/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:14 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/02/02 15:29:25 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    files_and_pipes(int *infile, int *outfile, int   *pipe_fd, char  **av)
{
    *infile = open(av[1],  O_CREAT | O_RDONLY | O_TRUNC, 0664);
    if (*infile == -1)
    {
        error_message(av[1]);
        exit(1);
    }
    *outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0664);
    if (*outfile == -1)
    {
        error_message("error opening");
        close(*infile);
        exit(1);
    }
    if (pipe(pipe_fd) == -1)
    {
        error_message("Pipe error");
        close(*infile);
        close(*outfile);
        exit(1);
    }
}

void    child_p1(int infile, int *pipe_fd, char *cmd, char **envp)
{
    dup2(pipe_fd[1], STDOUT_FILENO);
    dup2(infile, STDIN_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(infile);

    execution(cmd, envp);
    perror("Execution failed");
    exit(1);
}

void    child_p2(int outfile, int *pipe_fd, char *cmd, char **envp)
{
    dup2(pipe_fd[0], STDIN_FILENO);
    dup2(outfile, STDOUT_FILENO);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(outfile);

    execution(cmd, envp);
    perror("Execution failed");
    exit(1);
}

int main(int ac, char **av, char **envp)
{
    int pipe_fd[2];
    pid_t   pid1;
    pid_t   pid2;
    int outfile;
    int infile;

    if (ac != 5 || !*av[1] || !*av[2] || !*av[3] || !*av[4])
    {
        write(1, "Usage: ./pipex infile cmd1 cmd2 outfile\n", ft_strlen("Usage: ./pipex infile cmd1 cmd2 outfile\n"));
        return (1);
    }
    if (!av[2][0] || !av[3][0]) 
    {
        error_message("command arguments are empty");
        exit(1);
    }

    files_and_pipes(&infile, &outfile, pipe_fd, av);
    pid1 = fork();
    if (pid1 == 0)
        child_p1(infile, pipe_fd, av[2], envp);
    
    pid2 = fork();
    if (pid2 == 0)
        child_p2(outfile, pipe_fd, av[3], envp);
        
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(infile);
    close(outfile);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
