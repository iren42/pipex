/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:06:27 by iren              #+#    #+#             */
/*   Updated: 2022/04/30 17:14:04 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static void	child_con(t_pipex *pp)
{
	if (!ft_strncmp(pp->cmdnargs[0], "/", 1))
		{
			pp->cmd = pp->cmdnargs[0];
			if (access(pp->cmd, X_OK) != 0)
				piperror(ERR_CMD, CERR_CMD);
		}
		else
			pp->cmd = get_cmd(pp->env, pp->cmdnargs[0]);
		if (!pp->cmd)
		{
			free_tpipex(pp);
			piperror(ERR_CMD, CERR_CMD);
		}
		if (execve(pp->cmd, pp->cmdnargs, pp->env) == -1)
		{
			free_tpipex(pp);
			piperror(ERR_EXEC, CERR_EXEC);
		}

}

void	child1(t_pipex *pp)
{
	pp->infile = open(pp->raw_av[1], O_RDONLY);
	if (pp->infile == -1)
	{
		ft_putstr_fd("0\n", pp->outfile);
		close(pp->outfile);
		piperror(ERR_FD, 0);
	}
	dup2(pp->ends[1], STDOUT_FILENO);
	close(pp->ends[0]);
	close(pp->ends[1]);
	dup2(pp->infile, STDIN_FILENO);
	pp->cmdnargs = ft_split(pp->raw_av[2], ' ');
	if (pp->cmdnargs != 0)
		child_con(pp);
}

void	child2(t_pipex *pp)
{
	pp->outfile = open(pp->raw_av[4], O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (pp->outfile == -1)
		piperror(ERR_FD, CERR_FD);
	dup2(pp->ends[0], STDIN_FILENO);
	close(pp->ends[1]);
	close(pp->ends[0]);
	dup2(pp->outfile, STDOUT_FILENO);
	pp->cmdnargs = ft_split(pp->raw_av[3], ' ');
	if (pp->cmdnargs != 0)
		child_con(pp);
}
