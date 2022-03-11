/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:17:42 by iren              #+#    #+#             */
/*   Updated: 2022/03/11 16:54:22 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	piperror(const char *s, int errcode)
{
	perror(s);
	exit(errcode);
}

static char	*find_path(char **env)
{
	if (env != 0)
	{
		while (*env != 0)
		{
			if (ft_strncmp("PATH=", *env, 5) == 0)
				return (*env + 5);
			env++;
		}
	}
	return (0);
}

static void	init_get_cmd(char **tmp, char **res, char ***splitpaths, int *i)
{
	*tmp = 0;
	*res = 0;
	*splitpaths = 0;
	*i = 0;
}

static char	**get_splitpaths(char **env)
{
	char	**res;
	char	*path;

	res = 0;
	path = find_path(env);
	if (path == 0)
		return (0);
	res = ft_split(path, ':');
	return (res);
}

char	*get_cmd(char **env, char *cmd)
{
	char	*tmp;
	char	*res;
	char	**splitpaths;
	int		i;

	init_get_cmd(&tmp, &res, &splitpaths, &i);
	splitpaths = get_splitpaths(env);
	if (splitpaths != 0)
	{
		while (splitpaths[i])
		{
			tmp = ft_strjoin(splitpaths[i], "/");
			res = ft_strjoin(tmp, cmd);
			free(tmp);
			if (access(res, X_OK) == 0)
			{
				free_split(splitpaths);
				return (res);
			}
			free(res);
			i++;
		}
		free_split(splitpaths);
	}
	return (0);
}
