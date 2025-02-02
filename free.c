/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:04:03 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/01/31 19:49:57 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_array(char **arr)
{
    int i = 0;
    if (!arr) return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}
void    error_message(const char *msg)
{
    perror(msg);
}

void put_error(char *cmd)
{
    int i = 0;

    while (cmd[i])
        i++;
    write(2, cmd, i);
    write(2, ": command not found\n", 20);
}
