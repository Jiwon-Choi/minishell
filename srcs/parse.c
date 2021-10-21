/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 20:39:44 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/21 20:44:04 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redirect(t_cmd_lst *lst, int del)
{
	t_redirect	*new;
	int			i;

	new = redirect_new();
	if (ft_strncmp(lst->cmd[del], "<<", 2) == 0)
		new->type = DOUBLE;
	else if (*lst->cmd[del] == '<')
		new->type = SINGLE;
	else if (ft_strncmp(lst->cmd[del], ">>", 2) == 0)
		new->type = DOUBLE;
	else if (*lst->cmd[del] == '>')
		new->type = SINGLE;
	i = new->type;
	while (ft_isspace(lst->cmd[del][i]))
		i++;
	new->file = ft_substr(&(lst->cmd[del][i]), 0,
			ft_strlen(&(lst->cmd[del][i])));
	printf("!!!! (%s), (%s)\n", lst->cmd[del], new->file);
	lst->cmd = del_cmd(lst->cmd, del);
	return (EXIT_SUCCESS);
}

int	parse(t_cmd_lst *lst)
{
	int	i;

	while (lst)
	{
		i = 0;
		while (lst->cmd[i])
		{
			if (*lst->cmd[i] == '<' || *lst->cmd[i] == '>')
			{
				parse_redirect(lst, i);
				continue ;
			}
			i++;
		}
		printf("\n");
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}
