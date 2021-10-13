/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:53:43 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/13 15:49:51 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse(char *input)
{
	char	**arr = ft_split(input, '|');
	while (*arr)
		printf("%s\n", *arr++);
	return (0);
}

int		main(void)
{
	char	*s = "pwd | ls -al | wc -l";
	parse(s);
	return (0);
}
