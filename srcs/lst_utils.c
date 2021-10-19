/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:20:17 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/19 14:38:08 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_lst_add_back(t_cmd_lst **lst, t_cmd_lst *new)
{
	t_cmd_lst	*p;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	p = *lst;
	while (p->next)
		p = p->next;
	p->next = new;
}

t_cmd_lst	*cmd_lst_new(void)
{
	t_cmd_lst	*new;

	new = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	if (!new)
		return (0);
	new->cmd = (char **)malloc(sizeof(char *));
	if (!new->cmd)
		return (0);
	new->cmd[0] = NULL;
	new->in = NULL;
	new->out = NULL;
	new->next = NULL;
	return (new);
}

char	**cmd_cmd_add_back(char **old_cmd, char *input)
{
	int		size;
	char	**new;
	char	**p;

	size = 0;
	while (old_cmd[size])
		size++;
	size++;
	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return ((char **)EXIT_FAILURE);
	int i = 0;
	while (old_cmd[i])
	{
		new[i] = old_cmd[i];
		i++;
	}
	new[i++] = input;
	new[i] = NULL;
	return (new);
}
