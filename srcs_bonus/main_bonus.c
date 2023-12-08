/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:12:58 by mgovinda          #+#    #+#             */
/*   Updated: 2023/12/08 16:19:13 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_file_opener(char *path, int innout)
{
	int	ret;

	if (innout == 0)
	{
		if (access(path, F_OK | R_OK) == 0)
			ret = open(path, O_RDONLY);
		else
			ft_eq("Cannot access file");
	}
	else if (innout == 1)
		ret = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		ret = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
	return (ret);
}

void	ft_heredoc_sdin(char **argv, int *super_pipe)
{
	char	*ret;

	ret = NULL;
	close(super_pipe[0]);
	if (argv[2][0] == '\0')
		argv[2] = "\n";
	while (1)
	{
		ft_printf(1, "here_doc> ");
		ret = get_next_line(0);
		if (ft_strncmp(ret, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(ret);
			exit(0);
		}
		ft_putstr_fd(ret, super_pipe[1]);
		free(ret);
	}	
}

void	ft_heredoc(char **argv)
{
	int		super_pipe[2];
	pid_t	pid;

	if (pipe(super_pipe) == -1)
		ft_eq("Pipe creation error :");
	pid = fork();
	if (pid == -1)
		ft_eq("fork error :");
	if (!pid)
		ft_heredoc_sdin(argv, super_pipe);
	else
	{
		close(super_pipe[1]);
		dup2(super_pipe[0], 0);
		wait(NULL);
	}
}

static void	ft_here_starter(int *i, int argc, char **argv, int *f2)
{
	*i = 3;
	if (argc < 6)
		ft_argc_error_heredoc(argv[0]);
	*f2 = ft_file_opener(argv[argc - 1], 2);
	if (*f2 < 0)
		ft_eq("Error opening file2 :");
	ft_heredoc(argv);
}

int	main(int argc, char **argv, char **envp)
{
	int	f1;
	int	f2;
	int	i;

	if (argc < 5)
		ft_argc_error(argv[0]);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		ft_here_starter(&i, argc, argv, &f2);
	else
	{
		i = 2;
		f1 = ft_file_opener(argv[1], 0);
		if (f1 < 0)
			ft_eq("Error opening file1 :");
		f2 = ft_file_opener(argv[argc - 1], 1);
		if (f2 < 0)
			ft_eq("Error opening file2 :");
		dup2(f1, 0);
	}
	while (i < argc - 2)
		ft_piping(argv[i++], envp);
	dup2(f2, 1);
	ft_exec(argv[argc - 2], envp);
	return (EXIT_SUCCESS);
}
