/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:17:42 by iren              #+#    #+#             */
/*   Updated: 2022/03/09 11:20:33 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	piperror(const char *s, int errcode)
{
	(void)errcode;
	perror(s);
	exit(1);
}

int	open_file(char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		piperror(ERR_FD, errno);
	}
	return (fd);
}

char	*find_path(char **env)
{
	while (ft_strncmp("PATH=", *env, 5))
		env++;
	return (*env + 5);
}

char	*get_cmd(char **split, char *cmd)
{
	char	*tmp;
	char	*res;

	while (*split)
	{
		tmp = ft_strjoin(*split, "/");
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(res, R_OK | X_OK) == 0)
		{
			return (res);
		}
		free(res);
		split++;
	}
	return (NULL);
}

void	free_tpipex(t_pipex *pp)
{
	int	i;

	i = 0;
	if (pp->splitpaths != 0)
	{
		while (pp->splitpaths[i] != 0)
		{
			free(pp->splitpaths[i]);
			i++;
		}
		free(pp->splitpaths);
		pp->splitpaths = 0;
	}
	i = 0;
	if (pp->cmdnargs != 0)
	{
		while (pp->cmdnargs[i] != 0)
		{
			free(pp->cmdnargs[i]);
			i++;
		}
		free(pp->cmdnargs);
		pp->cmdnargs = 0;
	}
}
