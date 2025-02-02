/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:04:03 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/02/02 19:49:36 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	error_message(const char *msg)
{
	perror(msg);
}

void	put_error(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		write(2, cmd, ft_strlen(cmd)),
		write(2, ": No such file or directory\n", 28);
	}
	else
	{
		write(2, cmd, ft_strlen(cmd)),
		write(2, ": command not found\n", 20);
	}
}
