/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:36 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/02/03 21:17:46 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	handle_exec_error(char *expath, t_pipex *pipex, char *cmd)
{
	put_error(cmd);
	free(expath);
	free_cmd(pipex->cmd1);
	free_cmd(pipex->cmd2);
	exit(127);
}

static	void	execve_error(char *expath, t_pipex *pipex)
{
	perror("execve failed");
	free(expath);
	free_cmd(pipex->cmd1);
	free_cmd(pipex->cmd2);
	exit(1);
}

static	void	handle_cmd_error(t_pipex *pipex)
{
	free_cmd(pipex->cmd1);
	free_cmd(pipex->cmd2);
	exit(1);
}

static	char	*get_command_path(char **cmd, char **envp)
{
	char	*expath;

	if (cmd && ft_strchr(cmd[0], '/'))
	{
		expath = ft_strdup(cmd[0]);
		if (!expath)
			return (NULL);
	}
	else
		expath = extract_path(cmd[0], envp);
	return (expath);
}

void	execution(t_pipex *pipex, char **envp, int n_cmd)
{
	char	*expath;
	char	**cmd;

	cmd = NULL;
	if (!n_cmd)
		cmd = pipex->cmd1;
	else if (n_cmd == 1)
		cmd = pipex->cmd2;
	if (!cmd || !*cmd)
		handle_cmd_error(pipex);
	expath = get_command_path(cmd, envp);
	if (!expath || access(expath, X_OK) == -1)
		handle_exec_error(expath, pipex, cmd[0]);
	if (execve(expath, cmd, envp) == -1)
		execve_error(expath, pipex);
}
