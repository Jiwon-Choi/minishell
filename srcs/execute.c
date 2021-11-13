/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:51:15 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/13 19:44:58 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_path(char **envp, char *cmd)
{
	char	**path_arr;
	char	*path;
	char	**p;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			path_arr = ft_split((*envp + 5), ':');
		envp++;
	}
	p = path_arr;
	while (*p)
	{
		path = ft_strjoin(*p, "/");
		free(*p);
		*p = path;
		path = ft_strjoin(*p, cmd);
		free(*p);
		*p = path;
		p++;
	}
	return (path_arr);
}

int	execute(t_cmd *cmd, char **envp)
{
	int		pipefd[2];
	int		status;
	pid_t	pid;
	char	**path;

	path = make_path(envp, cmd->argv[0]);
	pipe(pipefd);
	pid = fork();
	if (pid > 0) // parent
	{
		waitpid(pid, &status, 0);
	}
	else if (pid == 0) // child
	{
		while (*path)
			execve(*path++, cmd->argv, envp);
		error_handler("command not found");
	}
	/*
	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
	*/
	return (EXIT_SUCCESS);
}
