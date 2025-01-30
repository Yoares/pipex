/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:41 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/01/30 15:16:04 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef PIPEX_H
#define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"

char *extract_path(char *cmd, char **envp);
void execution(char *av, char **envp);
void free_array(char **arr);
void    error_message(const char *msg);