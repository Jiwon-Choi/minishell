/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:53:43 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/18 20:13:15 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_list_add_back(t_cmd_list **lst, t_cmd_list *new)
{
	t_cmd_list	*p;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	p = *lst;
	while (p->next)
		p = p->next;
	p->next = new;
}

char	*parse_unit(char **input)
{
	int	i;
	int	quote;
	char	*start;
   
	start = *input;
	quote = NO_QUOTE;
	while (ft_isspace(**input))
		(*input)++;
	while (!ft_isspace(**input))
	{
		if (**input == '\"')
			quote = DOUBLE_QUOTE;
		else if (**input == '\'')
			quote = SINGLE_QUOTE;
		if (quote)
		{
			(*input)++;
			printf("---%c---\n", QUOTE[quote]);
			while (**input != QUOTE[quote])
				(*input)++;
			quote = NO_QUOTE;
		}
		(*input)++;
	}
	i = *input - start;
	printf("%d\n", i);
	return (0);
}

t_cmd_list	*parse_command(char *input)
{
	t_cmd_list	*new;
	
	new = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!new)
		return ((t_cmd_list *)EXIT_FAILURE);
	new->cmd = ft_split(input, ' ');
//	parse_unit(&input);
	return (new);
}

t_cmd_list	*parse(char *input)
{
	t_cmd_list	*lst;
	t_cmd_list	*new;
	char	**arr = ft_split(input, '|');

	while (*arr)
	{
		char	*line = ft_strtrim(*arr, " ");
		new = parse_command(line);
		cmd_list_add_back(&lst, new);
		arr++;
	}
	return (lst);
}

int		main(void)
{
	t_cmd_list	*cmd_list;

	cmd_list = parse("pwd | cat -e | echo -n \"abcd       \" \"hi\"| grep -r");
	while (cmd_list)
	{
		while (*cmd_list->cmd)
			printf("[%s]\n", *(cmd_list->cmd++));
		printf("\n\n");
		cmd_list = cmd_list->next;
	}
	return (0);
}
