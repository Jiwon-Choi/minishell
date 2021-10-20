/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:43:17 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/20 15:57:42 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_quote(char **res, char **input)
{
	int		quote;
	char	*start;

	quote = NONE;
	while (ft_isspace(**input))
		(*input)++;
	if (!**input)
		return (EXIT_SUCCESS);
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
					return (error_handler("unclosed quote"));
				(*input)++;
			}
			quote = NONE;
		}
		(*input)++;
	}
	*res = ft_substr(start, 0, *input - start);
	return (EXIT_SUCCESS);
}

int	split_command(t_cmd_lst **new, char *input)
{
	char	*split_res;

	*new = cmd_lst_new();
	split_res = NULL;
	if (!*new)
		return (error_handler("malloc failed in cmd_lst_new()"));
	while (*input)
	{
		if (split_quote(&split_res, &input))
			return (EXIT_FAILURE);
		(*new)->cmd = add_cmd((*new)->cmd, split_res);
		if (!((*new)->cmd))
			return (error_handler("malloc failed in add_cmd()"));
	}
	return (EXIT_SUCCESS);
}

int	split_line(t_cmd_lst **cmd_lst, char *input)
{
	t_cmd_lst	*new;
	char		**arr;
	int			i;

	new = NULL;
	arr = ft_split(input, '|');
	i = 0;
	while (arr[i])
	{
		if (split_command(&new, arr[i++]))
			return (EXIT_FAILURE);
		cmd_lst_add_back(cmd_lst, new);
	}
	free(arr);
	return (EXIT_SUCCESS);
}
