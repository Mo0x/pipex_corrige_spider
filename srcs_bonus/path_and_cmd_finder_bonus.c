/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_and_cmd_finder_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:04:35 by mgovinda          #+#    #+#             */
/*   Updated: 2023/12/05 15:04:40 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_array(void **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

static char	**slasher(char **paths)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
		{
			ft_free_array((void **)paths);
			return (NULL);
		}	
		free(paths[i]);
		paths[i] = tmp;
		i++;
	}
	return (paths);
}

char	**path_finder(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (envp[i])
	{
		envp[i] = envp[i] + 5;
		paths = ft_split(envp[i], ':');
		paths = slasher(paths);
	}
	return (paths);
}

char	*command_finder(char **paths, char *cmd)
{
	char	*ret;
	int		i;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (paths[i])
	{
		ret = ft_strjoin(paths[i], cmd);
		if (access(ret, F_OK | X_OK) == 0)
			return (ret);
		free(ret);
		i++;
	}
	return (NULL);
}
