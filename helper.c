/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:36 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/01/30 15:07:34 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*extract_path(char *cmd, char **envp)
{
    char **path;
    char *fullpath;
    
    int i;
    i = 0;
    while(envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
        i++;
    if (envp[i] == NULL)
        return NULL;
    path = ft_split(envp[i] + 5, ':');
    while (path && path[i])
    {
        fullpath = ft_strjoin(path[i], "/");
        fullpath = ft_strjoin(fullpath, cmd);
        if (access(fullpath, X_OK) == 0)
        {
            free_array(path);
            return fullpath;
        }
        free(fullpath);
        i++;
    }
    free_array(path);
    return NULL;
}

void	execution(char *av, char **envp)
{
    char **cmd;
    char *expath;
    
    cmd = ft_split(av, ' ');
    
    if (!cmd)
    {
        free_array(cmd);
        return 1;
    }
    if (ft_strchr(cmd[0], '/'))
    {
        expath = cmd[0];        
    }
    else 
        extract_path(expath, envp);
        
    if (!expath || access(expath, X_OK) == -1)
    {
        free_array(cmd);
        if (expath && expath != cmd[0])
			free(expath);
        return;
    }
    execve(expath, cmd, envp);
    free_array(cmd);
}