/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 13:56:15 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/01 12:05:13 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_redirect(char **input)
{
	int		redirect;

	redirect = NONE;
	if (ft_strncmp(*input, "<<", 2) == 0)
		redirect = DOUBLE;
	else if (**input == '<')
		redirect = SINGLE;
	else if (ft_strncmp(*input, ">>", 2) == 0)
		redirect = DOUBLE;
	else if (**input == '>')
		redirect = SINGLE;
	*input += redirect;
	while (ft_isspace(**input))
		(*input)++;
	if (**input == '\'' || **input == '\"')
	{
		if (pass_quotes(input))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	split_command(char **res, char **input)
{
	char	*start;

	while (ft_isspace(**input))
		(*input)++;
	start = *input;
	if (**input == '<' || **input == '>')
	{
		if (split_redirect(input))
			return (EXIT_FAILURE);
		(*input)++;
	}
	while (**input && **input != ' ')
	{
		if (**input == '<' || **input == '>')
			break ;
		else if (**input == '\'' || **input == '\"')
			if (pass_quotes(input))
				return (EXIT_FAILURE);
		(*input)++;
	}
	*res = ft_substr(start, 0, *input - start);
	return (EXIT_SUCCESS);
}

int	parse_command(t_cmd **new, char *line)
{
	char	*res;

	while (*line)
	{
		if (split_command(&res, &line))
			return (EXIT_FAILURE);
		if (*res == '<' || *res == '>')
		{
			redir_add_back(&((*new)->redirect), redir_new(res));
			free(res);
		}
		else if (*res)
			(*new)->argv = cmd_argv_add_back((*new)->argv, res);
	}
	return (EXIT_SUCCESS);
}
