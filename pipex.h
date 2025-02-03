/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:41 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/02/03 16:58:38 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_pipex
{
	char	*infile_path;
	char	*outfile_path;
	int		infile_fd;
	int		outfile_fd;
	char	**cmd1;
	char	**cmd2;
	int		pipe_fd[2];
}	t_pipex;

char	*extract_path(char *cmd, char **envp);
void	execution(t_pipex *pipex, char **envp, int n_cmd);
void	free_array(char **arr);
void	error_message(const char *msg);
void	files_and_pipes(t_pipex *pipex);
void	child_p1(t_pipex *pipex, char **envp);
void	child_p2(t_pipex *pipex, char **envp);
void	free_array(char **arr);
void	put_error(char *cmd);
void	free_cmd(char **cmd);
void	cleanup_and_wait(t_pipex *pipex, pid_t pid1, pid_t pid2);
#endif
