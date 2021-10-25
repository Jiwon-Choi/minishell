/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 20:39:44 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/25 15:44:47 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_quote(char **input, int *i)
{
	while (*input[*i] != '\'')
		(*i)++;
	return (EXIT_SUCCESS);
}

/*
char	*ft_getenv(char **envp)
{
	char	*res;

	res = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, key, ft_strlen(key)) == 0)
			res = getenv(*envp);
		envp++;
	}
	return (res);
}
*/

char	*ft_getkey(char *input)
{
	char	*start;

	start = input;
	while (*input && !ft_isspace(*input))
		input++;
	return (ft_substr(start, 0, input - start));
}

int	parse_replace(char **input, char **envp)
{
	int		i;
	char	*key;

	(void)envp;
	i = 0;
	while (*input[i])
	{
		if (*input[i] == '\'' && i++)
			pass_quote(input, &i);
		else if (*input[i] == '$')
		{
			key = ft_getkey(input[i]);
			printf("$$$%s$$$\n", key);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	parse_redirect(t_cmd_lst *lst, int del)
{
	t_redirect	**redirect_lst;
	t_redirect	*new;
	int			i;

	redirect_lst = NULL;
	new = redirect_new();
	if (*lst->cmd[del] == '<')
		redirect_lst = &(lst->in);
	else if (*lst->cmd[del] == '>')
		redirect_lst = &(lst->out);
	if (ft_strncmp(lst->cmd[del], "<<", 2) == 0)
		new->type = DOUBLE;
	else if (*lst->cmd[del] == '<')
		new->type = SINGLE;
	else if (ft_strncmp(lst->cmd[del], ">>", 2) == 0)
		new->type = DOUBLE;
	else if (*lst->cmd[del] == '>')
		new->type = SINGLE;
	i = new->type;
	while (ft_isspace(lst->cmd[del][i]))
		i++;
	new->file = ft_substr(&(lst->cmd[del][i]), 0,
			ft_strlen(&(lst->cmd[del][i])));
	redirect_add_back(redirect_lst, new);
	lst->cmd = del_cmd(lst->cmd, del);
	return (EXIT_SUCCESS);
}

int	parse(t_cmd_lst *lst, char **envp)
{
	int	i;

	(void)envp;
	while (lst)
	{
		i = 0;
		while (lst->cmd[i])
		{
			if (*lst->cmd[i] == '<' || *lst->cmd[i] == '>')
			{
				parse_redirect(lst, i);
				continue ;
			}
			i++;
		}
		lst = lst->next;
	}
//	parse_env_val(input, envp);
	return (EXIT_SUCCESS);
}
