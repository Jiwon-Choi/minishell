/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:43:17 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/19 18:04:56 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_quote(char **input)
{
	int		quote;
	char	*start;

	quote = NONE;
	while (ft_isspace(**input))
		(*input)++;
	if (!**input)
		return (0);
	start = *input;
	while (**input && !ft_isspace(**input))
	{
		if (**input == '\"' && (*input)++)
			quote = DOUBLE;
		else if (**input == '\'' && (*input)++)
			quote = SINGLE;
		if (quote)
		{
			while (**input != QUOTE[quote])
			{
				if (!**input)
					error_handler("quote");
				(*input)++;
			}
			quote = NONE;
		}
		(*input)++;
	}
	return (ft_substr(start, 0, *input - start));
}

t_cmd_lst	*split_command(char *input)
{
	t_cmd_lst	*new;
	char		**new_cmd;

	new = cmd_lst_new();
	if (!new)
		return ((t_cmd_lst *)EXIT_FAILURE);
	while (*input)
	{
		new_cmd = add_cmd(new->cmd, split_quote(&input));
		free(new->cmd);
		new->cmd = new_cmd;
	}
	return (new);
}

t_cmd_lst	*split_line(char *input)
{
	t_cmd_lst	*lst;
	t_cmd_lst	*new;
	char		**arr;

	lst = NULL;
	arr = ft_split(input, '|');
	while (*arr)
	{
		new = split_command(*arr);
		cmd_lst_add_back(&lst, new);
		arr++;
	}
	return (lst);
}
