/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbulanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:57:04 by rbulanad          #+#    #+#             */
/*   Updated: 2023/02/14 08:36:42 by rbulanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	openfilez(t_pp *var, char *infile, char *outfile)
{
	var->infile = open(infile, O_RDONLY, 0777);
	if (var->infile == -1)
		errormsg(var, "INFILE ERRROR");
	var->outfile = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (var->outfile == -1)
		errormsg(var, "OUTFILE ERROR");
}

void	execparams(t_pp *var, char *cmd, char **envp)
{
	var->argexec = ft_split(cmd, ' ');
	var->path = getpath(envp, var->argexec[0]);
}

void	childfunc(t_pp *var, char **envp, int *fd)
{
	int	pid;

	if (pipe(fd) == -1)
		errormsg(var, "PIPE ERROR");
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(var->path, var->argexec, envp);
	}
	waitpid(pid, NULL, 0);
	free_execve(var);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	lastcmd(t_pp *var, char **envp, int *fd)
{
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(var->outfile, STDOUT_FILENO);
		close(fd[1]);
		execve(var->path, var->argexec, envp);
	}
	waitpid(pid, NULL, 0);
	free_execve(var);
	close(fd[1]);
	close(fd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pp	*var;
	int		i;
	int		fd[2];

	if (argc < 4)
		errormsg(NULL, "NOT ENOUGH ARGS");
	var = malloc(sizeof(t_pp));
	openfilez(var, argv[1], argv[argc - 1]);
	dup2(var->infile, STDIN_FILENO);
	i = 2;
	while (i < argc - 2)
	{
		execparams(var, argv[i], envp);
		if (!var->path)
			error_structfree(var, "CMD ERROR");
		childfunc(var, envp, fd);
		i++;
	}
	execparams(var, argv[i], envp);
	if (!var->path)
		error_structfree(var, "CMD ERROR");
	lastcmd(var, envp, fd);
	return (free(var), 0);
}
