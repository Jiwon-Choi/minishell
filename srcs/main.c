/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:53:43 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/19 15:34:57 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_cmd_lst	*cmd_list;

	cmd_list = parse("pwd | cat -e | echo -n \"abcd    \"\"hi\"| grep -r  ");
	while (cmd_list)
	{
		while (*cmd_list->cmd)
			printf("[%s]\n", *(cmd_list->cmd++));
		printf("\n");
		cmd_list = cmd_list->next;
	}
	return (0);
}
