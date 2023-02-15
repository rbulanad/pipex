/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:01:41 by rbulanad          #+#    #+#             */
/*   Updated: 2023/02/13 17:23:37 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(t_pp *var, char *arg, char **envp)
{
	int	i;

	i = 0;
	dup2(var->pipefd[1], STDOUT_FILENO);
	dup2(var->file1, STDIN_FILENO);
	close(var->pipefd[0]);
	var->args = ft_split(arg, ' ');
	var->path = getpath(var->args[0], envp);
	if (!var->path)
	{
		i = 0;
		while (var->args[i])
			free(var->args[i++]);
		free(var->args);
		free(var->path);
		msg("PATH1");
		exit(1);
	}
	execve(var->path, var->args, envp);
}

void	child2(t_pp *var, char *arg, char **envp)
{
	int	i;

	i = 0;
	dup2(var->pipefd[0], STDIN_FILENO);
	dup2(var->file2, STDOUT_FILENO);
	close(var->pipefd[1]);
	var->args = ft_split(arg, ' ');
	var->path = getpath(var->args[0], envp);
	if (!var->path)
	{
		i = 0;
		while (var->args[i])
			free(var->args[i++]);
		free(var->args);
		free(var->path);
		msg("PATH2");
		exit(1);
	}
	execve(var->path, var->args, envp);
}

void	fileopen(t_pp *var, char *arg1, char *arg4)
{
	var->file1 = open(arg1, O_RDONLY, 0644);
	var->file2 = open(arg4, O_WRONLY | O_TRUNC | O_CREAT, 0644);
}

int	main(int argc, char **argv, char **envp)
{
	t_pp	*var;

	var = malloc(sizeof(t_pp));
	if (argc != 5)
		return (free(var), msg("ARGC ERROR"));
	fileopen(var, argv[1], argv[4]);
	if (var->file1 < 0)
		return (free(var), msg("INFILE ERROR"));
	if (var->file2 < 0)
		return (free(var), msg("OUTFILE ERROR"));
	if (pipe(var->pipefd) < 0)
		return (free(var), msg("PIPE ERROR"));
	var->pid1 = fork();
	if (var->pid1 == 0)
		child1(var, argv[2], envp);
	var->pid2 = fork();
	if (var->pid2 == 0)
		child2(var, argv[3], envp);
	close(var->pipefd[0]);
	close(var->pipefd[1]);
	waitpid(var->pid1, NULL, 0);
	waitpid(var->pid2, NULL, 0);
	free(var);
	return (0);
}
