/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:32:33 by mgovinda          #+#    #+#             */
/*   Updated: 2023/12/04 15:51:20 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/includes/libft.h"

void	ft_argc_error(char *n);
void	ft_eq(char *msg);
void	ft_error_path(char *cmd);
int		ft_file_opener(char *path, int innout);
void	ft_free_array(void **tab);
char	**path_finder(char **envp);
char	*command_finder(char **paths, char *cmd);
int		ft_exec(char *cmd, char **envp);
int		ft_piping(char *cmd, char **envp);
void	ft_argc_error_heredoc(char *n);

#endif