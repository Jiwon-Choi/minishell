/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:00:58 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/02 23:04:16 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
//	char	*line = "  ec\"ho\">>out -n< in$USER \'$USER \'$USER | grep -r ";
	char	*line = "e\"ch\"o $$USER";

	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	cmd = NULL;
	printf("%s\n", line);
	if (parse_line(&cmd, line, envp))
		return (EXIT_FAILURE);
	printf("--------------------\n");
	//free(cmd);

	int i = 1;
	while (cmd)
	{
		printf("%d\n", i++);
		while (*cmd->argv)
			printf("[%s]\n", *cmd->argv++);
		printf("redirect\n");
		while (cmd->redirect)
		{
			printf("[%d %s]\n", cmd->redirect->type, cmd->redirect->file);
			cmd->redirect = cmd->redirect->next;
		}
		printf("\n");
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
