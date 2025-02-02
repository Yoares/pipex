/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:36 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/02/02 14:39:37 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *extract_path(char *cmd, char **envp)
{
    char    **path;
    char    *fullpath;
    int i;
    
    i = 0;
    while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
        i++;
    if (envp[i] == NULL)
        return NULL;
    path = ft_split(envp[i] + 5, ':');
    i = 0;
    while (path && path[i])
    {
        fullpath = ft_strjoin(path[i], "/");
        fullpath = ft_strjoin(fullpath, cmd);
        if (access(fullpath, F_OK) == 0)
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

void    execution(char *av, char **envp)
{
    char    **cmd;
    char    *expath = NULL;

    cmd = ft_split(av, ' ');
    if (!cmd)
        free_array(cmd);
    if (ft_strchr(cmd[0], '/'))
    {
        expath = cmd[0];
    }
    else
        expath = extract_path(cmd[0], envp);
    
    if (!expath || access(expath, X_OK) == -1)
    {
        put_error(cmd[0]);
        free_array(cmd);
        if (expath) 
            free(expath);
        exit(127);
    }
    execve(expath, cmd, envp);
    perror("Error");
    exit(126);
}
