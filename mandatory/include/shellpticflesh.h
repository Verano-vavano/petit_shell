/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:16:15 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/03 13:49:39 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELLPTICFLESH_H
# define SHELLPTICFLESH_H

# include "libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

enum	e_cmd_part
{
	UNDEFINED,
	COMMAND,
	IN_FILE,
	OUT_FILE,
	HERE_DOC_DELIM,
	OUT_FILE_APP,
	DELIM,
	ERROR
};

typedef struct s_command
{
	char				*content;
	enum e_cmd_part		purpose;
	struct s_command	*next;
}				t_command;

// shellpticflesh
int			cmd_processing(char *cmd);

/*---------------LINE COMPREHENSION------------------*/
// line_comprehension
t_command	*understand_the_line(char *line);

// checker
int			sub_command_check(t_command *cmd, char *s);
int			redirection_check(t_command *cmd, char *s);
int			meta_check(t_command *cmd);

// parse_args
t_command	*ft_split_cmd(char *cmd, t_command *cmd_args);

// parse_args_utilities
int			ft_strlen_arg(char *s, int meta);
int			n_words(char *s);

/*---------------FILES------------------*/
int			here_doc(t_command *cmd);

/*---------------UTILITIES------------------*/
// cleaning
void		free_linked_list(t_command *l);

// cute_utils
t_command	*init_command_arg(t_command *start);
int			is_needy(char *s);
int			is_strict_meta(char c);
int			is_metachar(char c);
int			is_separator(char c);
int			is_delim(char c);
int			is_ender(char c, char new_c);

// error_manager
void		syntax_error(char *token);

#endif
