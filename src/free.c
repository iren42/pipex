/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:46:03 by iren              #+#    #+#             */
/*   Updated: 2022/03/11 16:46:19 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split != 0)
	{
		while (split[i] != 0)
		{
			free(split[i]);
			i++;
		}
		free(split);
		split = 0;
	}
}

void	free_tpipex(t_pipex *pp)
{
	free_split(pp->cmdnargs);
	free(pp->cmd);
}
