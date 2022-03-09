/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:07:33 by iren              #+#    #+#             */
/*   Updated: 2022/03/09 14:11:43 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>

# include "libft.h"

# define ERR_CMD "Error command not found"
# define CERR_CMD 0
# define ERR_ARGS "Error number of arguments"
# define CERR_ARGS 1
# define ERR_FORK "Error fork()"
# define CERR_FORK 1
# define ERR_EXEC "Error execve()"
# define CERR_EXEC 1
# define ERR_FD "Error open()"
# define CERR_FD 1 

typedef struct s_pipex
{
	int		err_counter;
	int		ends[2];
	int		infile;
	int		outfile;
	pid_t	pid1;
	pid_t	pid2;
	char	**raw_av;
	char	**env;
	char	*cmd;
	char	**cmdnargs;
	char	**splitpaths;
}				t_pipex;

int		open_file(char *filename, int flags);
char	*find_path(char **env);
char	*get_cmd(char **split, char *cmd);
void	piperror(const char *s, int errcode);
void	free_tpipex(t_pipex *pp);
void	free_split(char **split);

#endif
