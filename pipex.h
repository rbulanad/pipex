/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:45:58 by rbulanad          #+#    #+#             */
/*   Updated: 2023/02/14 12:52:54 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

typedef struct s_pp
{
	int		pipefd[2];
	int		pid1;
	int		pid2;
	int		file1;
	int		file2;
	char	*path;
	char	**args;
}t_pp;

int			len(const char *s);
char		*substr2(char *s, int start, int end);
char		**ft_split(char *s, char c);
char		*ft_strjoin(char *s1, char *s2);
int			msg(char *err);
char		*checkaccess(char **allpaths, char *cmd);
char		*getpath(char *cmd, char **env);

#endif
