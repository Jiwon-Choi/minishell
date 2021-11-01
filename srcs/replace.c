/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:40:11 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/11/01 18:39:00 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sh_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = 0;
	return (join);
}

int	add_char(char **str, char ch)
{
	char	*ch_str;
	char	*new;

	ch_str = (char *)malloc(2);
	ch_str[0] = ch;
	ch_str[1] = 0;
	new = sh_strjoin(*str, ch_str);
	free(*str);
	free(ch_str);
	*str = new;
	return (EXIT_SUCCESS);
}

int	get_env(char **res, char *str, char **envp, int *idx)
{
	int		key_size;
	char	*key;
	char	*val;

	key_size = 0;
	while (str[key_size] && str[key_size] != '\"' && str[key_size] != '\'' && str[key_size] != ' ')
		key_size++;
	key = ft_substr(str, 0, key_size);
	val = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, key + 1, ft_strlen(key + 1)) == 0)
			val = getenv(*envp);
		envp++;
	}
//	printf("key : [%s]\n", key + 1);
//	printf("input res : [%s]\n", *res);
//	printf("val : [%s]\n", val);
	*res = sh_strjoin(*res, val);
	*idx += key_size;
//	free(key);
//	free(val);
	return (EXIT_SUCCESS);
}

int	replace_env(char **input, char **envp)
{
	int		i;
	int		quote;
	char	*res;

	i = 0;
	quote = NONE;
	res = NULL;
	while ((*input)[i])
	{
		if ((*input)[i] == '\"' && quote == NONE)
			quote = DOUBLE;
		else if ((*input)[i] == '\'' && quote == NONE)
			quote = SINGLE;
		else if ((*input)[i] == '$' && quote != SINGLE)
			get_env(&res, &((*input)[i]), envp, &i);
		else if ((*input)[i] != QUOTE[quote])
			add_char(&res, (*input)[i]);
		else if ((*input)[i] == QUOTE[quote])
			quote = NONE;
		i++;
	}
	free(*input);
	*input = res;
	return (EXIT_SUCCESS);
}

int	replace(t_cmd *cmd, char **envp)
{
	char	**p;

	p = cmd->argv;
	(void)envp;
	while (*p)
	{
		printf(">>> [%s]\n", *p);
		replace_env(p, envp);
		printf(">>> [%s]\n\n", *p);
		p++;
	}
	return (EXIT_SUCCESS);
}
