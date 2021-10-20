/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:32:13 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/10/20 15:11:34 by jiwchoi          ###   ########.fr       */
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

# define NONE 0
# define SINGLE 1
# define DOUBLE 2

# define QUOTE "\0\'\""

typedef int		t_bool;

typedef struct s_redirect
{
	int					type;
	char				*file;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_cmd_lst
{
	char				**cmd;
	struct s_direct		*in;
	struct s_direct		*out;
	struct s_cmd_lst	*next;
}						t_cmd_lst;

// error.c
void		*error_return_null(char *err_msg);
// main.c

// split.c
char		*split_quote(char **input);
t_cmd_lst	*split_command(char *input);
t_cmd_lst	*split_line(char *input);

// utils_cmd_lst.c
void		cmd_lst_add_back(t_cmd_lst **lst, t_cmd_lst *new);
t_cmd_lst	*cmd_lst_new(void);
char		**add_cmd(char **old_cmd, char *input);

// utils_redirect.c
void		redirect_add_back(t_redirect **lst, t_redirect *new);
t_redirect	*redirect_new(void);

#endif
