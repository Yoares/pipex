/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:03:31 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/02/03 21:19:55 by ykhoussi         ###   ########.fr       */
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
