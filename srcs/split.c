/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:43:17 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/20 15:11:48 by jiwchoi          ###   ########.fr       */
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
		return (NULL);
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
					return (error_return_null("unclosed quote"));
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
	char		*split_res;

	new = cmd_lst_new();
	if (!new)
		return (NULL);
	while (*input)
	{
		split_res = split_quote(&input);
		new->cmd = add_cmd(new->cmd, split_res);
	}
	return (new);
}

t_cmd_lst	*split_line(char *input)
{
	t_cmd_lst	*lst;
	t_cmd_lst	*new;
	char		**arr;
	int			i;

	lst = NULL;
	arr = ft_split(input, '|');
	i = 0;
	while (arr[i])
	{
		new = split_command(arr[i++]);
		cmd_lst_add_back(&lst, new);
	}
	free(arr);
	return (lst);
}
