/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:55:44 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/01 15:26:48 by jiwchoi          ###   ########.fr       */
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

int	parse_line(t_cmd **cmd_lst, char *line, char **envp)
{
	t_cmd	*cmd;
	char	*res;

	if (*line == '|')
		return (error_handler("syntax error near unexpected token \'|\'"));
	while (*line)
	{
		if (split_line(&res, &line))
			return (EXIT_FAILURE);
		if (!*res)
			return (error_handler("syntax error near unexpected token \'|\'"));
		cmd = cmd_new();
		if (!cmd)
			return (error_handler("malloc error in cmd_new()"));
		if (parse_command(&cmd, res))
			return (EXIT_FAILURE);
		if (replace(cmd, envp))
			return (EXIT_FAILURE);
		cmd_add_back(cmd_lst, cmd);
		free(res);
	}
	return (EXIT_SUCCESS);
}
