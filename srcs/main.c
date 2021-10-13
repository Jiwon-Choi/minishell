/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:53:43 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/13 19:30:50 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_unit(char **space, char **input)
{
	int			i;

	while (ft_isspace(**input))
		(*input)++;
	if (ft_strchr(*input, ' '))
	   i = ft_strchr(*input, ' ') - *input;
	else
		i = ft_strlen(*input);
	*space = ft_substr(*input, 0, i);
	*input = *input + i;
}

t_command	*parse_command(char *input)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	parse_unit(&(new->cmd), &input);
	parse_unit(&(new->opt), &input);
	parse_unit(&(new->args), &input);
	printf("[%s], [%s], [%s]\n", new->cmd, new->opt, new->args);
	return (new);
}

t_command	*parse(char *input)
{
	char	**arr = ft_split(input, '|');

	while (*arr)
	{
		char	*line = ft_strtrim(*arr, " ");
		parse_command(line);
		arr++;
	}
	return (0);
}

int		main(void)
{
	char	*input;

	input = readline(">> ");
	parse(input);
	return (0);
}
