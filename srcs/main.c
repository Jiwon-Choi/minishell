/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:31:34 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/07 20:42:59 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)envp;
	printf("Hello minishell\n");

	char *arr[3];
	arr[0] = "pwd";
	arr[1] = "-L";
	arr[2] = 0;
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
