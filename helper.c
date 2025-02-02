/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:36 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/02/02 19:37:40 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	execution(char *av, char **envp)
{
	char	**cmd;
	char	*expath;

	cmd = ft_split(av, ' ');
	if (!cmd || !cmd[0]) 
	{
		free_array(cmd);
		exit(1);
	}	
	if (cmd[0] && ft_strchr(cmd[0], '/'))
		expath = ft_strdup(cmd[0]);
	else
		expath = extract_path(cmd[0], envp);

	if (!expath || access(expath, X_OK) == -1)
	{
		put_error(cmd[0]);
		free_array(cmd);
		free(expath);
		exit(127);
	}
	execve(expath, cmd, envp);
	write(2, "execve failed\n", 14);
	free_array(cmd);
	free(expath);
	exit(1);
}
