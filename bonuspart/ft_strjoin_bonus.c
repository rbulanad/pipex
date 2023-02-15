/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:12:54 by rbulanad          #+#    #+#             */
/*   Updated: 2023/02/14 14:52:06 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	ret = malloc ((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i++] = '/';
	while (s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}

char	*freejoin(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	return (ret);
}

void	error_structfree(t_pp *var, char *msg)
{
	int	i;

	i = 0;
	if (var)
	{
		if (var->path)
			free(var->path);
		if (var->argexec)
		{
			if (var->argexec[i])
			{
				while (var->argexec[i])
					free(var->argexec[i++]);
				free(var->argexec);
			}
		}
		free(var);
	}
	perror(msg);
	exit(1);
}

void	errormsg(t_pp *var, char *msg)
{
	if (var)
		free(var);
	perror(msg);
	exit(1);
}
