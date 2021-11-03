/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:00:58 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/03 18:03:55 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line = "  ec\"ho\">>out -n< $abc \'$dfsdf \'$$123 | grep -r | grep -r";
//	char	*line = "cat <<$USER";

	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	cmd = NULL;
	if (parse_line(&cmd, line, envp))
		return (EXIT_FAILURE);
	//free(cmd);

	printf("%s\n", line);
	printf("--------------------\n");
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
