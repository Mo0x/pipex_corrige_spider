/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_and_cmd_finder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgovinda <mgovinda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:38:24 by mgovinda          #+#    #+#             */
/*   Updated: 2023/12/08 17:01:55 by mgovinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	while (ft_strncmp(envp[i], "PATH", 4))
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
		return (ft_strdup(cmd));
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
