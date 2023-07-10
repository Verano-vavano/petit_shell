/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:16:15 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/10 18:36:40 by tcharanc         ###   ########.fr       */
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

# define TEMP "/tmp/temp_shellptic_"

# define PS1 "lol >> "
# define PS2 "> "

enum	e_cmd_part
{
	UNDEFINED,
	COMMAND,
	IN_FILE,
	OUT_FILE,
	HERE_DOC_DELIM,
	OUT_FILE_APP,
	IN_OUT_FILE,
	REDIR_ID,
	DELIM,
	ERROR
};

typedef struct s_command
{
	char				*content;
	enum e_cmd_part		purpose;
	struct s_command	*next;
}				t_command;

typedef struct s_env
{
	char			*key;
	char			**value;
	struct s_env	*next;
}				t_env;

// shellpticflesh
int			cmd_processing(char *line, t_env *env);

/*--------------SPLIT-----------------*/
t_command	*spliter_init(char *cmd);

/*---------------LINE COMPREHENSION------------------*/
// line_comprehension
int			understand_the_line(t_command *cmd);

// syntax checker
int			check_syntax(char *line);

// purposer
int			redirection_check(t_command *cmd, char *s);
int			meta_check(t_command *cmd);

// parse_args
t_command	*ft_split_cmd(char *cmd);
char		rescue_funk(char *s, t_command *now_arg, int *i, char c);

// parse_args_utilities
int			handle_parenthesis(char *c, char c2, int dos);
int			ft_strlen_arg(char *s, int meta);

/*---------------HEREDOC------------------*/
void		unlink_heredocs(t_command *cmd);
int			here_doc(t_command *cmd);

/*--------------EXPANSIONS-----------------*/
int			line_expansions(t_command *lexed);

/*--------------EXECUTION-----------------*/
void		execute_the_line(t_command *cmd);

/*---------------UTILITIES------------------*/
// cleaning
void		free_command(t_command *l);
void		free_env(t_env *env);
void		free_whole_env(t_env *env);

// utils
t_command	*init_command_arg(t_command *start);

// char_utils
int			is_strict_meta(char c);
int			is_metachar(char c);
int			is_separator(char c);
int			is_delim(char c);
int			is_ender(char c, char new_c);

// more_char_utils
char		convert_to_closing(char c);
int			is_cmd_delim(char *c);
int			is_num(char c);

// error_manager
int			syntax_error(char *token, int l);

/*---------------BUILTINS------------------*/
void		metal_injection(void);
void		exit_hell(t_command *lexed);
void		echo_des_enfers(t_command *lexed);
void		env_infernal(t_env *env, ...);
void		les_ex_portes_de_lenfer(t_command *lexed, t_env *env);

/*----------------ENV---------------------*/
t_env		*env_processing(char **envp);
/*----------------ENV_UTILS----------------*/
void		add_env(t_env **env, t_env *newest);
t_env		*env_last(t_env *env);

#endif
