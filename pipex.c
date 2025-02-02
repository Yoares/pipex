/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:14 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/02/02 20:59:11 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init(t_pipex *pipex, char	**av)
{
	pipex->infile = av[1];
	pipex->outfile = av[4];
	
}
void	files_and_pipes(t_pipex *pipex)
{
	
	pipex->infile = open(pipex->infile, O_RDONLY);
	if (pipex->infile == -1)
	{
		error_message(pipex->infile);
		exit(1);
	}
	pipex->outfile = open(pipex->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (pipex->outfile== -1)
	{
		error_message("error opening");
		close(pipex->infile);
		exit(1);
	}
	if (pipe(pipex->pipe_fd) == -1)
	{
		error_message("Pipe error");
		close(pipex->infile);
		close(pipex->outfile);
		exit(1);
	}
}

void	child_p1(t_pipex *pipex, char **envp)
{
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);	
	dup2(pipex->infile, STDIN_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	close(pipex->infile);
	close(pipex->outfile);
	execution(pipex->cmd, envp);
	perror("Execution failed");
	exit(1);
}

void	child_p2(int outfile, int *pipe_fd, char *cmd, char **envp)
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

int	main(int ac, char **av, char **envp)
{
	t_pipex * pipex;
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5 || !*av[1] || !*av[2] || !*av[3] || !*av[4])
	{
		write(1, "Usage: ./pipex infile cmd1 cmd2 outfile\n",
			ft_strlen("Usage: ./pipex infile cmd1 cmd2 outfile\n"));
		return (1);
	}
	if (!av[2][0] || !av[3][0])
	{
		error_message("command arguments are empty");
		exit(1);
	}
	init(pipex,av);
	files_and_pipes(pipex);
	pid1 = fork();
	if (pid1 == 0)
		child_p1(pipex, envp);
	pid2 = fork();
	if (pid2 == 0)
		child_p2(pipex->outfile, pipex->pipe_fd, av[3], envp);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	close(pipex->infile);
	close(pipex->outfile);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
