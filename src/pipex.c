/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:06:27 by iren              #+#    #+#             */
/*   Updated: 2022/03/08 22:16:05 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child1(t_pipex *pp)
{
	dup2(pp->ends[1], STDOUT_FILENO);
	close(pp->ends[0]);
	close(pp->ends[1]);
	dup2(pp->infile, STDIN_FILENO);
	pp->cmdnargs = ft_split(pp->raw_av[2], ' ');
	pp->cmd = get_cmd(pp->splitpaths, pp->cmdnargs[0]);
	if (!pp->cmd)
		piperror(ERR_CMD);
	if (execve(pp->cmd, pp->cmdnargs, pp->env) == -1)
		piperror(ERR_EXEC);
}

static void	child2(t_pipex *pp)
{
	dup2(pp->ends[0], STDIN_FILENO);
	close(pp->ends[1]);
	close(pp->ends[0]);
	dup2(pp->outfile, STDOUT_FILENO);
	pp->cmdnargs = ft_split(pp->raw_av[3], ' ');
	pp->cmd = get_cmd(pp->splitpaths, pp->cmdnargs[0]);
	if (!pp->cmd)
		piperror(ERR_CMD);
	if (execve(pp->cmd, pp->cmdnargs, pp->env) == -1)
		piperror(ERR_EXEC);
}

static void	init(t_pipex *pp, char **av, char **env)
{
	pp->env = env;
	pp->err_counter = 0;
	pp->raw_av = av;
	pipe(pp->ends);
	pp->infile = open_file(pp->raw_av[1], O_RDONLY);
	pp->outfile = open_file(pp->raw_av[4], O_CREAT | O_RDWR | O_TRUNC);
	pp->splitpaths = ft_split(find_path(pp->env), ':');
}

static void	ft_wait(t_pipex *pp)
{
	int	status;

	waitpid(pp->pid1, &status, 0);
	if (WIFEXITED(status))
		pp->err_counter += WEXITSTATUS(status);
	waitpid(pp->pid2, &status, 0);
	if (WIFEXITED(status))
		pp->err_counter += WEXITSTATUS(status);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pp;

	if (ac != 5)
		piperror(ERR_ARGS);
	init(&pp, av, env);
	pp.pid1 = fork();
	if (pp.pid1 < 0)
		piperror(ERR_FORK);
	if (pp.pid1 == 0)
		child1(&pp);
	pp.pid2 = fork();
	if (pp.pid2 < 0)
		piperror(ERR_FORK);
	if (pp.pid2 == 0)
		child2(&pp);
	close(pp.ends[0]);
	close(pp.ends[1]);
	ft_wait(&pp);
	return (pp.err_counter);
}
