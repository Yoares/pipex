/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:14 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/02/03 20:29:13 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init(t_pipex *pipex, char **av)
{
	pipex->infile_path = av[1];
	pipex->outfile_path = av[4];
	pipex->cmd1 = ft_split(av[2], ' ');
	if (!pipex->cmd1)
	{
		perror("Error splitting cmd1");
		exit(EXIT_FAILURE);
	}
	pipex->cmd2 = ft_split(av[3], ' ');
	if (!pipex->cmd2)
	{
		free_cmd(pipex->cmd1);
		perror("Error splitting cmd2");
		exit(EXIT_FAILURE);
	}
}

void	files_and_pipes(t_pipex *pipex)
{
	pipex->infile_fd = open(pipex->infile_path, O_RDONLY);
	if (pipex->infile_fd == -1)
	{
		error_message(pipex->infile_path);
		exit(EXIT_FAILURE);
	}
	pipex->outfile_fd = open(pipex->outfile_path,
			O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (pipex->outfile_fd == -1)
	{
		error_message("error opening");
		close(pipex->infile_fd);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipex->pipe_fd) == -1)
	{
		error_message("Pipe error");
		close(pipex->infile_fd);
		close(pipex->outfile_fd);
		exit(EXIT_FAILURE);
	}
}

void	child_p1(t_pipex *pipex, char **envp)
{
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	dup2(pipex->infile_fd, STDIN_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	close(pipex->infile_fd);
	close(pipex->outfile_fd);
	execution(pipex, envp, 0);
	perror("Execution failed");
	exit(EXIT_FAILURE);
}

void	child_p2(t_pipex *pipex, char **envp)
{
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	dup2(pipex->outfile_fd, STDOUT_FILENO);
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	close(pipex->outfile_fd);
	close(pipex->infile_fd);
	execution(pipex, envp, 1);
	perror("Execution failed");
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	

	if (ac != 5 || !*av[1] || !*av[2] || !*av[3] || !*av[4])
	{
		write(1, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
		return (EXIT_FAILURE);
	}
	init(&pipex, av);
	files_and_pipes(&pipex);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		child_p1(&pipex, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		child_p2(&pipex, envp);
	cleanup_and_wait(&pipex, pipex.pid1, pipex.pid2);
	if (pipex.cmd1)
		free_cmd(pipex.cmd1);
	if (pipex.cmd2)
		free_cmd(pipex.cmd2);
	return (EXIT_SUCCESS);
}
