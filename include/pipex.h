/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:07:33 by iren              #+#    #+#             */
/*   Updated: 2022/03/10 09:56:05 by iren             ###   ########.fr       */
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
# include <stdlib.h>

# define ERR_CMD1 "Error command not found: cmd1"
# define ERR_CMD2 "Error command not found: cmd2"
# define CERR_CMD 127
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

char	*find_path(char **env);
char	*get_cmd(char **split, char *cmd);
void	piperror(const char *s, int errcode);
void	free_tpipex(t_pipex *pp);

char	**ft_split(char const *str, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
