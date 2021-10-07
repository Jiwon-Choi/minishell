/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:31:34 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/07 21:17:21 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_path(char **envp, char *cmd)
{
	char	**path_arr;
	char	*path;

	while (*envp)
	{
		if (strncmp(*envp, "PATH=", 5) == 0)
			path_arr = ft_split(*(envp + 5), ':');
		envp++;
	}
	while (*path_arr)
	{
		path = ft_strjoin(*path_arr, cmd);
		if (access(path, X_OK))
		{
			// free(path_arr);
			return (path);
		}
		free(path);
		path_arr++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	pid_t	pid;
	int		fildes[2];
	int		status;

	(void)argc;
	(void)argv;
	(void)envp;
	printf("Hello minishell\n");

	char *arr[3];
	arr[0] = "pwd";
	arr[1] = "-L";
	arr[2] = 0;

	pipe(fildes);
	pid = fork();
	while (1)
	{
		input = readline(">> ");
		if (*input && !ft_strncmp("exit", input, ft_strlen(input)))
			break ;
		if (!ft_strncmp("pwd", input, ft_strlen(input)))
			execve("/bin/pwd", arr, 0);
		printf("[%s]\n", input);
	}
	return (0);
}
