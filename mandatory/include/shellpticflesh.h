/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:16:15 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/14 17:53:27 by tcharanc         ###   ########.fr       */
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
	HERE_STRING,
	REDIR_ID,
	DELIM,
	CMD_DELIM,
	ERROR
};

typedef struct s_command
{
	char				*content;
	enum e_cmd_part		purpose;
	struct s_command	*next;
}				t_command;

typedef struct s_redir_pipe
{
	int					fd_read;
	int					fd_write;
	int					fd_end;
	char				*here_string;
	bool				opened_read;
	bool				opened_write;
	struct s_redir_pipe	*next;
}				t_redir_pipe;

typedef struct s_process_cmd
{
	char			**cmd;
	t_redir_pipe	*redir;
}				t_process_cmd;

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
// line_expansions
int			expand_cmd(t_command *cmd, t_env *env);

// braces_expansion
int			braces_expansion(t_command *cmd);

// tilde_expansion
void		tilde_expansion(t_command *cmd, t_env *env);

// get_tilde
char		*rescue_tilde_funk(t_env *env);

/*--------------EXECUTION-----------------*/
long		execute_the_line(t_command *cmd, t_env *env);

int			get_cmd(t_process_cmd *cmd_processing, t_command *cmd);

int			count_cmds(t_command *cmd);
void		free_redirs(t_redir_pipe *redir);

/*---------------UTILITIES------------------*/
// cleaning
int			free_command(t_command *l);
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
int			is_all_num(char *s);
char		is_quoted(char *s, int i, char quoted);

// error_manager
int			syntax_error(char *token, int l);
int			ambiguous_error(char *cmd);
int			some_error(char *cmd, char *error);

/*---------------BUILTINS------------------*/
void		metal_injection(void);
void		exit_hell(t_command *lexed);
void		echo_des_enfers(t_command *lexed);
void		env_infernal(t_env *env, ...);
void		les_ex_portes_de_lenfer(t_command *lexed, t_env *env);
void		unset_et_damnation(t_command *lexed, t_env *env);
void		cd_mentiel(t_command *lexed, t_env *env);
void		print_working_damnation();

/*----------------ENV---------------------*/
t_env		*env_new(char *env_var);
t_env		*env_init(char **envp);
/*----------------ENV_UTILS----------------*/
void		env_add(t_env *newest, t_env **env);
void		env_del(char *del, t_env **env);
t_env		*env_last(t_env *env);
char		**env_getval(char *key, t_env *env);
int			env_update(char *key, char **value, t_env *env);
t_env		*env_getptr(char *key, t_env *env);

#endif
