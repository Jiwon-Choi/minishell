/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:00:58 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/26 15:44:47 by jiwchoi          ###   ########.fr       */
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

	if (**input == ' ')
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

int	split_line(char **res, char **input)
{
	char	*start;

	if (**input == '|')
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

int	parse_command(char *line)
{
	char	*res;

	while (*line)
	{
		if (split_command(&res, &line))
			return (EXIT_FAILURE);
		if (*res)
			printf("-[%s]\n", res);
	}
	return (EXIT_SUCCESS);
}

int	parse_line(t_cmd **cmd, char *line)
{
	char	*res;

	(void)cmd;
	while (*line)
	{
		if (split_line(&res, &line))
			return (EXIT_FAILURE);
		printf("[%s]\n", res);
		parse_command(res);
		printf("\n");
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line = "echo>out -n< in \'$USER |=\'$USER ~|    cat    -e    | grep -r";

	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	(void)envp;
	cmd = NULL;
	if (parse_line(&cmd, line))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
