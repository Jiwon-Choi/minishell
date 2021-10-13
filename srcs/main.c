/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:31:34 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/13 14:52:39 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_path(char **envp, char *cmd)
{
	char	**path_arr;
	char	*path;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
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

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (s1[i] > s2[i])
		return (1);
	else if (s1[i] < s2[i])
		return (-1);
	else
		return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)envp;
	printf("Hello minishell\n");

	char *pwd[] = { "pwd", "-L", 0 };
	char *echo[] = { "echo", "-n", "abc", 0 };
//	char *touch[] = { "touch", "aaa", 0 };

	chdir(argv[1]);

	while (1)
	{
		input = readline(">> ");
		if (!*input)
			continue ;
		else if (!ft_strcmp("exit", input))
			break ;
		// parse
		if (!ft_strcmp("pwd", input))
			execve("/bin/pwd", pwd, 0);
		if (!ft_strcmp("echo", input))
			execve("/bin/echo", echo, 0);
		printf("[%s]\n", input);
	}
	return (0);
}
