/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:10:09 by mgovinda          #+#    #+#             */
/*   Updated: 2023/12/06 14:14:33 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_argc_error(char *name)
{
	char	*n;

	n = ft_strdup(&name[2]);
	ft_printf(2, "Error %s: %s requieres at least 4 arguments to work.\n", n, n);
	ft_printf(2, "Like the following : %s File1 Cmd1 Cmd2 ... CmdN File2\n", n);
	free(n);
	exit(EXIT_FAILURE);
}

void	ft_eq(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_error_path(char *cmd)
{
	ft_printf(2, "Error %s commmand not found check ", cmd);
	ft_printf(2, "spelling and retry !\n");
}

void	ft_argc_error_heredoc(char *n)
{
	ft_printf(2, "Error %s, usage with here_doc :\n", n);
	ft_printf(2, "here_doc LIMITER Cmd1, Cmd2 ... CmdN File2\n");
	exit(EXIT_FAILURE);
}
