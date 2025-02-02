/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhoussi <ykhoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:44:41 by ykhoussi          #+#    #+#             */
/*   Updated: 2025/02/01 18:38:51 by ykhoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
void files_and_pipes(int *infile, int *outfile, int *pipe_fd, char **av);
void    child_p1(int infile, int *pipe_fd, char *cmd, char **envp);
void    child_p2(int outfile, int *pipe_fd, char *cmd, char **envp);
void free_array(char **arr);
void put_error(char *cmd);
#endif