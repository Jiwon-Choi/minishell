/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:51:15 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/14 20:00:20 by jiwchoi          ###   ########.fr       */
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

void	ft_close(int fd)
{
	if (fd == STDIN_FILENO)
		return ;
	if (fd == STDOUT_FILENO)
		return ;
	if (fd == STDERR_FILENO)
		return ;
	close(fd);
}

int	wait_cmd(void)
{
	int	status;

	wait(&status);
	return (EXIT_SUCCESS);
}

int	execute(t_cmd *cmd, char **envp, int fd_in)
{
	int		pipefd[2];
	int		fd_out;
	pid_t	pid;

	if (!cmd)
		return (EXIT_SUCCESS);
	fd_out = STDOUT_FILENO;
	if (cmd->next)
	{
		pipe(pipefd);
		fd_out = pipefd[WRITE];
	}
	pid = fork();
	if (pid > 0)
	{
		ft_close(fd_in);
		ft_close(fd_out);
		wait_cmd();
//		waitpid(pid, &status, 0);
	}
	else if (pid == 0)
	{
		ft_close(pipefd[READ]);
		char **path = make_path(envp, cmd->argv[0]);
		while (*path)
			execve(*path++, cmd->argv, envp);
		exit(0);
		//error_handler("command not found");
	}
	/*
	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
	*/
	execute(cmd->next, envp, pipefd[READ]);
	return (EXIT_SUCCESS);
}
