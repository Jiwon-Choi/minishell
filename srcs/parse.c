/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:22:30 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/19 15:30:15 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_unit(char **input)
{
	int		quote;
	char	*start;

	quote = NO_QUOTE;
	while (ft_isspace(**input))
		(*input)++;
	if (!**input)
		return (0);
	start = *input;
	while (**input && !ft_isspace(**input))
	{
		if (**input == '\"' && (*input)++)
			quote = DOUBLE_QUOTE;
		else if (**input == '\'' && (*input)++)
			quote = SINGLE_QUOTE;
		if (quote)
		{
			while (**input != QUOTE[quote])
				(*input)++;
			quote = NO_QUOTE;
		}
		(*input)++;
	}
	return (ft_substr(start, 0, *input - start));
}

t_cmd_lst	*parse_command(char *input)
{
	t_cmd_lst	*new;
	char		**new_cmd;

	new = cmd_lst_new();
	if (!new)
		return ((t_cmd_lst *)EXIT_FAILURE);
	while (*input)
	{
		new_cmd = cmd_cmd_add_back(new->cmd, parse_unit(&input));
		free(new->cmd);
		new->cmd = new_cmd;
	}
	return (new);
}

t_cmd_lst	*parse(char *input)
{
	t_cmd_lst	*lst;
	t_cmd_lst	*new;
	char		**arr;

	lst = NULL;
	arr = ft_split(input, '|');
	while (*arr)
	{
		new = parse_command(*arr);
		cmd_lst_add_back(&lst, new);
		arr++;
	}
	return (lst);
}
