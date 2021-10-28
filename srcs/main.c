/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:00:58 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/28 12:09:43 by jiwchoi          ###   ########.fr       */
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
		if (*res == '<')
		{
			redir_add_back(&((*new)->in), redir_new(res));
			printf("-[%s]\n", res);
		}
		else if (*res == '>')
		{
			redir_add_back(&((*new)->out), redir_new(res));
			printf("-[%s]\n", res);
		}
		else if (*res)
		{
			(*new)->argv = cmd_argv_add_back((*new)->argv, res);
			printf("-[%s]\n", res);
		}
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
		printf("[%s]\n", res);
		if (parse_command(&new, res))
			return (EXIT_FAILURE);
		printf("\n");
		cmd_add_back(cmd, new);
		free(res);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line = "  echo>>out    -n<   in \'$USER |=\'$USER ~    | grep   -r  ";

	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	(void)envp;
	cmd = NULL;
	printf("%s\n", line);
	if (parse_line(&cmd, line))
		return (EXIT_FAILURE);
	printf("--------------------\n\n");
	//free(cmd);

	int i = 1;
	while (cmd)
	{
		printf("%d\n", i++);
		while (*cmd->argv)
			printf("[%s]\n", *cmd->argv++);
		printf("in\n");
		while (cmd->in)
		{
			printf("[%d %s]\n", cmd->in->type, cmd->in->file);
			cmd->in = cmd->in->next;
		}
		printf("out\n");
		while (cmd->out)
		{
			printf("[%d %s]\n", cmd->out->type, cmd->out->file);
			cmd->out = cmd->out->next;
		}
		printf("\n");
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
