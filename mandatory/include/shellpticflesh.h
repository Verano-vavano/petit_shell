/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:16:15 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/06 09:22:52 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELLPTICFLESH_H
# define SHELLPTICFLESH_H

# include "libft.h"
# include "sig.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TEMP "/tmp/temp_shellptic_"
# define READ 0
# define WRITE 1

# define PS1 "lol >> "
# define PS2 "> "
# define PROG_NAME "Minishell"
# define SHELL_NAME "Shellpticflesh"

# define STD_PATH "PATH=/.local/bin:/bin:/usr/local/bin:/usr/bin"

# define CLEAR_LINE "\033[K"

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
	MARKER,
	VAR_ASSIGN,
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
	char			*cmd_name;
	bool			is_builtin;
	t_redir_pipe	*redir;
	bool			free_name;
	bool			sub_cmd;
}				t_process_cmd;

typedef struct s_env
{
	char			*key;
	char			**value;
	bool			is_exported;
	struct s_env	*next;
}				t_env;

typedef struct s_hist_ll
{
	char				*content;
	struct s_hist_ll	*next;
}				t_hist_ll;

typedef struct s_hist
{
	int			len_hist;
	t_hist_ll	*hist_start;
	t_hist_ll	*hist_end;
}				t_hist;

typedef struct s_tools
{
	t_env	*env;
	char	**c_env;
	t_hist	*hist;
	long	rt_val;
}				t_tools;

typedef struct s_ret_cmd
{
	pid_t	pid;
	int		fd;
	int		pipes[2];
	int		n_cmd;
	int		*heredoc_no;
}				t_ret_cmd;

typedef struct s_list_file
{
	char				*content;
	struct s_list_file	*next;
}				t_lf;

// shellpticflesh
long		cmd_processing(char *line, t_tools *tools, bool add_line);

/*--------------SPLIT-----------------*/
t_command	*spliter_init(char *cmd, bool add_line, t_hist *hist, t_env *env);

/*---------------LINE COMPREHENSION------------------*/
// line_comprehension
int			understand_the_line(t_command *cmd);

// syntax checker
int			check_syntax(char *line);
int			check_metachar(char *line);
int			check_parenthesis(char *line, int first, int dollar);
int			check_cbrackets(char *line);
int			redir_ok(char *line);

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
int			get_heredoc_file(int hd, int mode);
void		unlink_heredocs(t_command *cmd);
int			here_doc(t_command *cmd, t_env *env);

/*--------------EXPANSIONS-----------------*/
// line_expansions
int			expand_cmd(t_command *cmd, t_tools *tools);

// braces_expansion
int			braces_expansion(t_command *cmd);
int			coma_brace_expansion(t_command *cmd, int *start_end);
int			dots_brace_expansion(t_command *cmd, int *se);
int			dots_expansion(t_command *cmd, char **param, int *se);

// tilde_expansion
void		tilde_expansion(t_command *cmd, t_env *env);

// get_tilde
char		*rescue_tilde_funk(t_env *env);

// parameter_expansion
void		parameter_expansion(t_command *cmd, t_tools *tools);
// utils
int			find_arg_len(char *s, bool brack, char quoted);
bool		is_special_param(char *arg);
char		*special_parameter(char *arg, t_tools *tools);

// command substitution
long		command_substitution(t_command *cmd, t_env *env);
char		*get_output(int *pipes);

// filename expansion
void		filename_expansion(t_command *cmd);
// subverif
void		get_all_valid_files(t_command *cmd, int index, t_lf *lf);
t_lf		*check_subfiles(t_command *cmd, int index, t_lf *lf, t_lf *nlf);
// file check
bool		is_valid_fe(char *file, char *matcher);
// lf
void		sort_lf(t_lf *lf);
void		add_lf_cmd(t_command *cmd, t_lf *lf);
void		free_lf(t_lf *lf);
void		add_to_lf(char *file, t_lf *lf);
t_lf		*remove_flf(t_lf *act, t_lf *lf);
// utils
int			get_path_star_fe(char *cnt);
char		*ft_strstr_fe(char *haystack, char *needle);
bool		not_over(char *s);
int			move_end_stars(char *qmat);

// word split
void		word_split(t_command *cmd, char *newer, int *se, t_env *env);
// utils
int			search_next_ifs(char *newer, char *ifs);
char		*get_ifs(t_env *env);

// quote removal
char		*quote_removal(char *cmd);
void		quote_remove_cmd(t_command *cmd);

/*--------------EXECUTION-----------------*/
// execution
long		execute_the_line(t_command *cmd, t_tools *tools, int *heredoc_no);

// execution_doer
void		check_hist(t_command *cmd, t_hist *hist, t_env *env, int n_cmd);
long		wait_father(t_ret_cmd *ret, int n_cmd, long err);
void		crt_child(t_process_cmd *cmd, t_tools *t, t_ret_cmd *ret);

// builtin_exec
long		exec_bltin(t_process_cmd *cmd, t_tools *t, bool one, char **c_env);

// get_cmd
int			handle_files(t_process_cmd *cmd_p, t_command *cmd, int hd);
int			get_cmd(t_process_cmd *cmd_processing, t_command *cmd, int *hd_no);

// files
int			open_redir_files(t_command *cmd, t_redir_pipe *redir, int hd);
void		close_files(t_redir_pipe *redir);
int			open_write_file(t_command *cmd, t_redir_pipe *redir);
int			open_read_file(t_command *cmd, t_redir_pipe *redir, int hd);

// get_path
int			get_cmd_path(t_process_cmd *cmd, t_env *env);
// check_path
bool		check_builtin(char *cmd, bool is_rel);
char		*check_path(char **paths, char *path_cmd);
int			check_org_path(char *cmd);
char		*add_start(char *cmd);

// redirections
void		perform_redirections(t_process_cmd *cmd, t_ret_cmd *ret);

// execution_utils
int			count_cmds(t_command *cmd);
void		free_redirs(t_redir_pipe *redir);
t_command	*go_to_next_cmd(t_command *cmd);
void		exec_cleaner(t_process_cmd cmd_processing);

/*--------------HISTORY--------------*/
t_hist		*load_history(t_env *env);
void		add_to_hist(t_env *env, t_hist *hist, char *line);
void		write_hist(t_hist *hist, t_env *env);
void		free_history(t_hist *hist);
char		*get_histfile(t_env *env);
int			get_histsize(char *type, int stdval, t_env *env);
void		remove_first_el(t_hist *hist);
void		add_all_hist(t_hist *hist);

/*--------PROMPT----------*/
char		*new_prompt(int n_ps, t_env *env);

/*---------------UTILITIES------------------*/
// cleaning
int			free_command(t_command *l);
void		free_env(t_env *env);
void		free_whole_env(t_env *env);

// utils
t_command	*init_command_arg(t_command *start);
bool		is_dir(char *path);
int			usearch(char *s, char c);
bool		is_file_valid(char *file, int mode);
bool		is_valid_var_char(char c);

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
int			command_error(char *cmd, int error);

// warnings
void		warning_heredoc_eof(int lines, char *eof);

// signals
void		sig_main(int sig);
void		sig_catch(int sig);
void		heredoc_handle(int sig);

/*---------------BUILTINS------------------*/
int			metal_injection(void);
void		exit_hell(char **cmd, long ret);
int			echo_des_enfers(char **cmd);
int			env_infernal(t_env *env, ...);
int			les_ex_portes_de_lenfer(char **cmd, t_env **env);
int			unset_et_damnation(char **cmd, t_env **env);
int			cd_mentiel(char **cmd, t_env *env);
int			print_working_damnation(void);
int			tetris(char **args);

/*----------------ENV---------------------*/
t_env		*env_new(char *env_var, bool is_exported);
t_env		*env_init(char **envp);
/*----------------ENV_UTILS----------------*/
void		env_add(t_env *newest, t_env **env);
void		env_del(char *del, t_env **env);
t_env		*env_last(t_env *env);
char		**env_getval(char *key, t_env *env);
void		env_change_val(char *key, char *value, t_env *env, bool is_exp);
void		env_update(char *char_arr, bool is_exported, t_env *env, ...);
t_env		*env_getptr(char *key, t_env *env);
int			env_contain(char *newest, t_env *env);
int			env_isdefined(char *key, t_env *env);
char		**re_char_etoile_etoilise_env(t_env *env);
void		env_create_add(char *key, char *value, t_env *env);

/*----------------TO_DELETE_UTILS----------------*/
void		print_char_arr(char **arr);
void		print_cmd(t_command *cmd);

#endif
