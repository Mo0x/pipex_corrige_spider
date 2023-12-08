/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:42:24 by mgovinda          #+#    #+#             */
/*   Updated: 2023/12/08 17:07:09 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	process_one(int f1, int *super_pipe, char *cmd, char **envp)
{
	char	**paths;
	char	**s_cmd;
	char	*ex;

	s_cmd = ft_split(cmd, ' ');
	paths = path_finder(envp);
	ex = command_finder(paths, s_cmd[0]);
	if (!ex)
	{
		ft_error_path(s_cmd[0]);
		ft_free_array((void **)paths);
		ft_free_array((void **)s_cmd);
		exit(EXIT_FAILURE);
	}
	dup2(f1, 0);
	dup2(super_pipe[1], 1);
	close(super_pipe[0]);
	execve(ex, s_cmd, envp);
	ft_free_array((void **)paths);
	ft_free_array((void **)s_cmd);
	if (ex)
		free(ex);
	return (0);
}

int	process_two(int f2, int *super_pipe, char *cmd, char **envp)
{
	char	**paths;
	char	**s_cmd;
	char	*ex;

	s_cmd = ft_split(cmd, ' ');
	paths = path_finder(envp);
	ex = command_finder(paths, s_cmd[0]);
	if (!ex)
	{
		ft_error_path(s_cmd[0]);
		ft_free_array((void **)paths);
		ft_free_array((void **)s_cmd);
		exit(EXIT_FAILURE);
	}
	dup2(f2, 1);
	dup2(super_pipe[0], 0);
	close(super_pipe[1]);
	execve(ex, s_cmd, envp);
	ft_free_array((void **)paths);
	ft_free_array((void **)s_cmd);
	if (ex)
		free(ex);
	return (0);
}

void	pipex(int f1, int f2, char **argv, char **envp)
{
	int		super_pipe[2];
	int		status;
	pid_t	child_1;
	pid_t	child_2;

	if (pipe(super_pipe) == -1)
		ft_eq("Pipe creation error :");
	child_1 = fork();
	if (child_1 < 0)
		ft_eq("Fork error: ");
	if (child_1 == 0)
		process_one(f1, super_pipe, argv[2], envp);
	child_2 = fork();
	if (child_2 < 0)
		ft_eq("Fork error: ");
	if (child_2 == 0)
		process_two(f2, super_pipe, argv[3], envp);
	close(super_pipe[0]);
	close(super_pipe[1]);
	waitpid(child_1, &status, 0);
	waitpid(child_2, &status, 0);
}
