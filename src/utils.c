/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:17:42 by iren              #+#    #+#             */
/*   Updated: 2022/03/08 22:15:11 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	piperror(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

int	open_file(char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		piperror("Could not open fd\n");
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
