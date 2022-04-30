/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:06:27 by iren              #+#    #+#             */
/*   Updated: 2022/04/30 17:14:19 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init(t_pipex *pp, char **av, char **env)
{
	pp->env = env;
	pp->raw_av = av;
	pp->err_counter = 0;
	pp->cmdnargs = 0;
	pp->cmd = 0;
	pipe(pp->ends);
}

static void	ft_wait(t_pipex *pp)
{
	int	status;

	waitpid(pp->pid1, &status, 0);
	waitpid(pp->pid2, &status, 0);
	if (WIFEXITED(status))
		pp->err_counter = WEXITSTATUS(status);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pp;

	if (ac != 5)
		piperror(ERR_ARGS, CERR_ARGS);
	init(&pp, av, env);
	pp.pid1 = fork();
	if (pp.pid1 < 0)
		piperror(ERR_FORK, CERR_FORK);
	if (pp.pid1 == 0)
		child1(&pp);
	pp.pid2 = fork();
	if (pp.pid2 < 0)
		piperror(ERR_FORK, CERR_FORK);
	if (pp.pid2 == 0)
		child2(&pp);
	close(pp.ends[0]);
	close(pp.ends[1]);
	ft_wait(&pp);
	free_tpipex(&pp);
	return (pp.err_counter);
}
