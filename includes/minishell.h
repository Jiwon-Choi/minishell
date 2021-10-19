/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:32:13 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/19 12:29:42 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h> //getenv
# include <stdio.h> //readline
# include <signal.h> //signal, kill
# include <term.h> // tget~
# include <termios.h> // tcget~
# include <dirent.h> // ~dir
# include <sys/stat.h> // ~stat
# include <sys/wait.h>
# include <readline/readline.h>

# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

# define NO_QUOTE 0
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2

# define QUOTE "\0\'\""

typedef int		t_bool;

typedef struct s_cmd_list
{
	char				**cmd;
	char				*in;
	char				*out;
	struct s_cmd_list	*next;
}						t_cmd_lst;

// lst_utils.c
void		cmd_lst_add_back(t_cmd_lst **lst, t_cmd_lst *new);
t_cmd_lst	*cmd_lst_new(void);
char		**cmd_cmd_add_back(char **old_cmd, char *input);

// main.c

// parse.c

char		*parse_unit(char **input);
t_cmd_lst	*parse_command(char *input);
t_cmd_lst	*parse(char *input);

#endif
