/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:36 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/02/03 17:16:16 by ykhoussi         ###   ########.fr       */
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

static	void	execve_error(char *expath, char **cmd, t_pipex *pipex)
{
	write(2, "execve failed\n", 14);
	free_array(cmd);
	free(expath);
	free_cmd(pipex->cmd1);
	free_cmd(pipex->cmd2);
	exit(1);
}

static	char	*join_path(char *path, char *cmd)
{
	char	*tmp;
	char	*fullpath;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	fullpath = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!fullpath)
		return (NULL);
	return (fullpath);
}

char	*extract_path(char *cmd, char **envp)
{
	char	**path;
	char	*fullpath;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path && path[i])
	{
		fullpath = join_path(path[i], cmd);
		if (access(fullpath, F_OK) == 0)
		{
			free_array(path);
			return (fullpath);
		}
		free(fullpath);
		i++;
	}
	free_array(path);
	return (NULL);
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
	{
		free_array(cmd);
		exit(1);
	}
	if (cmd && ft_strchr(cmd[0], '/'))
		expath = ft_strdup(cmd[0]);
	else
		expath = extract_path(cmd[0], envp);
	if (!expath || access(expath, X_OK) == -1)
		handle_exec_error(expath, pipex, cmd[0]);
	execve(expath, cmd, envp);
	execve_error(expath, cmd, pipex);
}
