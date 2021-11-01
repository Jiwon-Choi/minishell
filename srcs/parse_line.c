/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:55:44 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/28 14:42:03 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_quotes(char **input)
{
	int	quote;

	quote = NONE;
	if (**input == '\"' && (*input)++)
		quote = DOUBLE;
	else if (**input == '\'' && (*input)++)
		quote = SINGLE;
	while (**input != QUOTE[quote])
	{
		if (!**input)
			return (error_handler("unclosed quote"));
		(*input)++;
	}
	return (EXIT_SUCCESS);
}

int	split_line(char **res, char **input)
{
	char	*start;

	if (**input == '|')
		(*input)++;
	while (ft_isspace(**input))
		(*input)++;
	start = *input;
	while (**input && **input != '|')
	{
		if (**input == '\'' || **input == '\"')
			if (pass_quotes(input))
				return (EXIT_FAILURE);
		(*input)++;
	}
	*res = ft_substr(start, 0, *input - start);
	return (EXIT_SUCCESS);
}

int	parse_line(t_cmd **cmd, char *line)
{
	t_cmd	*new;
	char	*res;

	if (*line == '|')
		return (error_handler("syntax error near unexpected token \'|\'"));
	while (*line)
	{
		if (split_line(&res, &line))
			return (EXIT_FAILURE);
		if (!*res)
			return (error_handler("syntax error near unexpected token \'|\'"));
		new = cmd_new();
		if (!new)
			return (error_handler("malloc error in cmd_new()"));
		if (parse_command(&new, res))
			return (EXIT_FAILURE);
//		if (replace_env(*cmd))
//			return (EXIT_FAILURE);
		cmd_add_back(cmd, new);
		free(res);
	}
	return (EXIT_SUCCESS);
}
