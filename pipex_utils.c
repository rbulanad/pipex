/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:46:16 by rbulanad          #+#    #+#             */
/*   Updated: 2023/02/10 10:37:52 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	len(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*checkaccess(char **allpaths, char *cmd)
{
	char	*ret;
	int		i;

	i = 0;
	while (allpaths[i])
	{
		ret = ft_strjoin(allpaths[i++], cmd);
		if (access(ret, F_OK) == 0)
			return (ret);
	}
	free(ret);
	return (NULL);
}

char	*getpath(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	*envcpy;
	char	**allpaths;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][0 + 1] == 'A'
				&& env[i][0 + 2] == 'T' && env[i][0 + 3] == 'H')
			break ;
		i++;
	}
	envcpy = substr2(env[i], 5, len(env[i]));
	allpaths = ft_split(envcpy, ':');
	path = checkaccess(allpaths, cmd);
	if (!path)
		return (NULL);
	return (path);
}
