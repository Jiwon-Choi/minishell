/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:22:30 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/19 15:15:17 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_unit(char **input)
{
	int		i;
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
		if (**input == '\"')
			quote = DOUBLE_QUOTE;
		else if (**input == '\'')
			quote = SINGLE_QUOTE;
		if (quote)
		{
			(*input)++;
			while (**input != QUOTE[quote])
				(*input)++;
			quote = NO_QUOTE;
		}
		(*input)++;
	}
	i = *input - start;	
	return (ft_substr(start, 0, i));
}

t_cmd_lst	*parse_command(char *input)
{
	t_cmd_lst	*new;

	new = cmd_lst_new();
	if (!new)
		return ((t_cmd_lst *)EXIT_FAILURE);
	while (*input)
		new->cmd = cmd_cmd_add_back(new->cmd, parse_unit(&input));
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
