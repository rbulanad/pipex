/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:46:16 by rbulanad          #+#    #+#             */
/*   Updated: 2023/02/13 17:31:51 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	strfind(char *str, char *find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == find[j])
			j++;
		if (find[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*find_envline(char **envp)
{
	int	i;

	i = 0;
	while (strfind(envp[i], "PATH") == 0)
		i++;
	return (envp[i] + 5);
}

char	*getpath(char **envp, char *cmd)
{
	int		i;
	char	*envline;
	char	**pathtab;
	char	*path;

	envline = find_envline(envp);
	pathtab = ft_split(envline, ':');
	i = 0;
	while (pathtab[i])
	{
		path = freejoin(pathtab[i], cmd);
		if (access(path, F_OK) == 0)
		{
			freepathtab(pathtab, i);
			return (path);
		}
		free(path);
		i++;
	}
	return (free(pathtab), pathtab = NULL, NULL);
}

void	freepathtab(char **pathtab, int i)
{
	if (pathtab[i + 1] != NULL)
	{
		i++;
		while (pathtab[i])
			free(pathtab[i++]);
		free(pathtab);
		pathtab = NULL;
	}
}

void	free_execve(t_pp *var)
{
	int	i;

	i = 0;
	free(var->path);
	while (var->argexec[i])
		free(var->argexec[i++]);
	free(var->argexec);
	var->argexec = NULL;
}
