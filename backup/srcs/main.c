/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:41:14 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/25 19:00:09 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
//	char *str = "ls>out\"hi\" -l<in | wc";
	char *str = "<";

	t_cmd_lst	*cmd_lst;

	(void)argc;
	(void)argv;
	cmd_lst = NULL;
	if (split_line(&cmd_lst, str))
		return (EXIT_FAILURE);
	if (parse(cmd_lst, envp))
		return (EXIT_FAILURE);

	while (cmd_lst)
	{
		while (*cmd_lst->cmd)
			printf("[%s]\n", *cmd_lst->cmd++);
		printf("\n");
		cmd_lst = cmd_lst->next;
	}
	/*
	printf("in\n");
	while (cmd_lst->in)
	{
		printf("%d %s\n", cmd_lst->in->type, cmd_lst->in->file);
		cmd_lst->in = cmd_lst->in->next;
	}
	printf("out\n");
	while (cmd_lst->out)
	{
		printf("%d %s\n", cmd_lst->out->type, cmd_lst->out->file);
		cmd_lst->out = cmd_lst->out->next;
	}
	*/
	return (EXIT_SUCCESS);
}
