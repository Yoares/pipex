/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:14 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/02/01 17:04:21 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **envp)
{
    int pipe_fd[2];
    int pid1;
    pid_t pid2;
    
    if (ac != 5)
    {
        write(1,"Usage: ./pipex infile cmd1 cmd2 outfile\n",ft_strlen("Usage: ./pipex infile cmd1 cmd2 outfile\n"));
        return (1);
    }
    int infile = open(av[1], O_CREAT | O_RDONLY| O_TRUNC, 0664);
    if (infile == -1)
    {
        error_message(av[1]);
        return (1);
    }
    if (av[2] || av[3])
    {
        error_message("commend argument are empty");
    }
    int outfile = open(av[4], O_CREAT | O_WRONLY| O_TRUNC, 0664);
    if (outfile == -1)
    {
        error_message("error opening");
        close(infile);
        return (1);
    }
    if (pipe(pipe_fd) == -1)
    {
        error_message("pipe error");
        close(infile);
        close(outfile);
        return 1;
    }
    pid1 = fork();
    if (pid1 == 0)
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        dup2(infile, STDIN_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        close(infile);
        close(outfile);

        execution(av[1], envp);
        perror("Execution failed");
        exit(1);
    }
    
    pid2 = fork();
    if (pid2 == 0)
    {
        dup2(pipe_fd[0], STDIN_FILENO);
        dup2(outfile, STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        close(infile);
        close(outfile);
        
        execution(av[3], envp);
        perror("Execution failed");
        exit(1);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(infile);
    close(outfile);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);    
}