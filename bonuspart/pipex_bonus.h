/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 08:18:18 by rbulanad          #+#    #+#             */
/*   Updated: 2023/02/14 12:53:31 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_pp
{
	int		infile;
	int		outfile;
	int		nbargs;
	char	*path;
	char	**argexec;
}				t_pp;

int		ft_strlen(char *str);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*freejoin(char *s1, char *s2);
char	*substr2(char *s, int start, int end);
int		strfind(char *str, char *find);
char	*find_envline(char **envp);
char	*getpath(char **envp, char *cmd);
void	freepathtab(char **pathtab, int i);
void	free_execve(t_pp *var);
void	errormsg(t_pp *var, char *msg);
void	error_structfree(t_pp *var, char *msg);

#endif
