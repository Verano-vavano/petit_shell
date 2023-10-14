/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:16:15 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/14 17:46:26 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELLPTICFLESH_H
# define SHELLPTICFLESH_H

# include "libft.h"
# include "../printfd/printfd.h"
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

# define READ STDIN_FILENO
# define WRITE STDOUT_FILENO
# define ERR STDERR_FILENO

# define PROG_NAME "Minishell"
# define SHELL_NAME "Shellpticflesh"
# define SHELL_VERSION "1.0"

# define STD_PS1 "PS1=\\c0w\\cR\\s \\cG\\v \\cp[\\W] $(([ $? -ne 0 ] && echo -e \"\\e[1;31m\") || echo -e \"\\e[1;36m\")($?) \\cW> \\cw"
# define STD_LOW_PS1 "PS1=\\s-\\v\\$ "
# define STD_PS2 "PS2=\\cR|-> \\cw"
# define STD_LOW_PS2 "PS2=> "
# define STD_PATH "PATH=/.local/bin:/bin:/usr/local/bin:/usr/bin"

# define CLEAR_LINE "\033[K"

# define TEMP "/tmp/temp_shellptic_"
# define RC ".shellptrc"

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
	PS_EXP,
	ERROR
};

enum	e_quotes
{
	NOQUOTES,
	SQUOTES,
	DQUOTES,
	CQUOTES
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
	t_redir_pipe	*redir;
	bool			is_builtin;
	bool			sub_cmd;
	bool			is_parenthesis;
}				t_process_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			is_exported;
	struct s_env	*next;
}				t_env;

typedef struct s_hist_ll
{
	char				*content;
	long				num_cmd;
	struct s_hist_ll	*prev;
	struct s_hist_ll	*next;
}				t_hist_ll;

typedef struct s_hist
{
	int			len_hist;
	t_hist_ll	*hist_start;
	t_hist_ll	*hist_end;
}				t_hist;

typedef struct s_alias
{
	char			*cmd;
	char			*replacer;
	struct s_alias	*next;
}				t_alias;

typedef struct s_settings
{
	bool	rc;
	short	ps;
	bool	hist;
	int		c;
}				t_set;

typedef struct s_tool
{
	t_env	*env;
	char	**c_env;
	t_hist	*hist;
	t_alias	*alias_start;
	t_alias	*alias_end;
	t_set	settings;
	long	rt_val;
	char	*cwd;
}				t_tool;

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
long		cmd_processing(char *line, t_tool *tool, bool add_line);

long		line_beauty(t_command *lexed, t_tool *tool);
long		exit_processing(t_command *lexed, long rt_val);
long		exec_loop(t_command *lexed, t_tool *tool, int *hd_no);

long		execute_rc(int fd_rc, t_tool *tool);
void		exec_shellptrc(t_tool *tool);

void		assign_vars(t_command *cmd, t_env **env);

/*--------------SPLIT-----------------*/
t_command	*spliter_init(char **cmd, bool add_line, t_tool *tool);

/*---------------LINE COMPREHENSION------------------*/
// line_comprehension
int			understand_the_line(t_command *cmd);
bool		check_assign(char *s, bool exporting);

// syntax checker
int			check_syntax(char *line);
int			check_metachar(char *line);
int			check_parenthesis(char *line, int first, int dollar, int i);
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
int			here_doc(t_command *cmd, t_tool *tool);

/*------------COOL_GETTERS-------------*/
char		*get_username(char *name, t_env *env);
char		*get_home(t_env *env);
char		*get_hostname(char *name, t_env *env);
char		*get_arranged_cwd(t_env *env, bool only_end);

/*--------------EXPANSIONS-----------------*/
// line_expansions
int			expand_cmd(t_command *cmd, t_tool *tool);

// braces_expansion
int			braces_expansion(t_command *cmd);
int			coma_brace_expansion(t_command *cmd, int *start_end);
int			find_end(char *s);
char		*get_braces_ext(int *se, int *nodes, char *org);
int			dots_brace_expansion(t_command *cmd, int *se);
int			dots_expansion(t_command *cmd, char **param, int *se);

// tilde_expansion
void		tilde_expansion(t_command *cmd, t_env *env);

// parameter_expansion
int			parameter_expansion(t_command *cmd, t_tool *tool);
// utils
int			find_arg_len(char *s, bool brack, char quoted);
bool		is_special_param(char *arg);
char		*special_parameter(char *arg, t_tool *tool);
char		*backslash_it(char *p);

// command substitution
long		command_substitution(t_command *cmd, t_env *env, bool only_repl);
char		*get_output(int *pipes);
int			command_it(char *cmd_sent, int *se, t_command *cmd, t_env *env);

// filename expansion
int			filename_expansion(t_command *cmd);
// subverif
void		get_all_valid_files(t_command *cmd, int index, t_lf *lf);
t_lf		*check_subfiles(t_command *cmd, int index, t_lf *lf, t_lf *nlf);
// file check
bool		is_valid_fe(char *file, char *matcher);
// lf
void		sort_lf(t_lf *lf);
void		add_lf_cmd(t_command *cmd, t_lf *lf, int purpose);
void		free_lf(t_lf *lf);
void		add_to_lf(char *file, t_lf *lf);
t_lf		*remove_flf(t_lf *act, t_lf *lf);
// utils
int			get_path_star_fe(char *cnt);
char		*ft_strstr_fe(char *haystack, char *needle);
bool		not_over(char *s);
int			move_end_stars(char *qmat);

// alias expansion
void		alias_expansion(t_command *cmd, t_tool *tool);
t_alias		*get_alias(char *content, t_alias *alias);
t_command	*al_add_new_command(char *s, int l, t_command *n, t_command **st);

// word split
int			word_split(t_command *cmd, char *newer, int *se, t_env *env);
void		merge_it(t_command *cmd, t_command *to_merge, int *se);
// utils
int			search_next_ifs(char *newer, char *ifs);
char		*get_ifs(t_env *env);

// quote removal
char		*quote_removal(char *cmd);
void		quote_remove_cmd(t_command *cmd);

/*--------------EXECUTION-----------------*/
// execution
long		execute_the_line(t_command *cmd, t_tool *tool, int *heredoc_no);

// execution_mainloop
long		ex_loop(t_command **cmd, t_tool *tool, t_ret_cmd *ret, int *n_cmd);

// execution loop utils
void		init_cp(t_process_cmd *cmd_processing, t_tool *t, t_command *cmd);
bool		has_command(t_command *cmd);

// execution_doer
void		check_hist(t_command *cmd, t_tool *tool, int n_cmd);
long		wait_father(t_ret_cmd *ret, int n_cmd, long err);
void		crt_child(t_process_cmd *cmd, t_tool *t, t_ret_cmd *ret);

// builtin_exec
long		exec_bltin(t_process_cmd *cmd, t_tool *t, bool one);

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
char		*check_path(char *path, char *path_cmd);
int			check_org_path(char *cmd);
char		*add_start(char *cmd);

// redirections
void		perform_redirections(t_process_cmd *cmd, t_ret_cmd *ret);

// execution_utils
int			count_cmds(t_command *cmd);
void		free_redirs(t_redir_pipe *redir);
t_command	*go_to_next_cmd(t_command *cmd);
void		exec_cleaner(t_process_cmd cmd_processing);
void		close_pipes(int *pipes);

/*--------------HISTORY--------------*/
t_hist		*load_history(t_env *env);
void		add_to_hist(t_env *env, t_hist *hist, char *line);
void		write_hist(t_hist *hist, t_env *env);
void		free_history(t_hist *hist, bool free_big);
char		*get_histfile(t_env *env);
int			get_histsize(char *type, int stdval, t_env *env);
void		remove_first_el(t_hist *hist);
void		add_all_hist(t_hist *hist);
void		add_hist_struct(t_hist *hist, char *line, int histsize);

void		print_whole_hist(t_hist *hist);
void		print_index_hist(t_hist *hist, long index);
int			print_range_hist(long range, t_hist *hist);

/*--------PROMPT----------*/
char		*new_prompt(int n_ps, t_tool *tool);
void		print_ps0(t_tool *tool);
char		*ps_cool_expansion(char *ps, t_tool *tool);
char		*prompt_color(char *s, int *to_repl);

/*---------------UTILITIES------------------*/
// cleaning
int			free_command(t_command *l);
void		free_env(t_env *env);
void		free_whole_env(t_env *env);
void		free_alias(t_alias *alias);
void		free_tool(t_tool *tool);

// utils
t_command	*init_command_arg(t_command *start);
int			usearch(char *s, char c);
bool		is_file_valid(char *file, int mode);
bool		is_valid_var_char(char c);

// file_utils
bool		is_dir(char *path);
bool		is_lnk(char *path);
bool		is_blk(char *path);
bool		is_reg(char *path);
bool		is_empty_file(char *path);

// file_utils2
bool		is_chr(char *path);
bool		is_fifo(char *path);
bool		is_sock(char *path);
bool		is_gid(char *path);
bool		is_uid(char *path);

// file_two_utils
bool		files_ef(char *file1, char *file2);
bool		files_nt(char *file1, char *file2);
bool		files_ot(char *file1, char *file2);

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
char		is_quoted_bk(char *s, int i, char quoted, bool bk);

// word_utils
char		*replace_escaped(char *cmd, int i);

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
int			exit_hell(char **cmd, long ret, t_tool *tool, bool one);
int			echo_des_enfers(char **cmd);
int			printferno(char **cmd);
int			env_infernal(t_env *env, bool exported);
int			les_ex_portes_de_lenfer(char **cmd, t_env **env);
t_env		*dup_env(t_env *env);
void		sort_env(t_env *head);
int			unset_et_damnation(char **cmd, t_env **env);
int			cd_mentiel(char **cmd, t_tool **tool);
void		change_oldpwd(t_env **env);
void		change_pwd(char *dest, t_tool **t);
int			print_working_damnation(char *cwd);
int			hellias(char **args, t_tool *tool);
void		sort_alias(t_tool *tool);
void		print_whole_alias(t_tool *tool);
bool		print_alias(char *arg, t_tool *tool);
int			unhellias(char **cmd, t_tool *t);
int			beastory(char **cmd, t_tool *t);
int			source_of_styx(char **cmd, t_tool *t);
int			print_formated_hell(char **cmd);
int			tetris(char **args);

int			test_satanism(char **cmd);
int			double_expr_test(char **cmd, char *cmd_name);
int			single_expr_test(char **cmd, char *cmd_name);
int			test_three(char **cmd);
int			test_two(char **cmd);
char		**go_to_end(char **cmd, char *cmd_name, int *in_par);
int			search_and_perform_test(char **cmd, char *cmd_name, int narg);

/*----------------ENV---------------------*/
t_env		*env_new(char *env_var, bool is_exported);
char		**one_split(char *str, char c);
t_env		*env_init(char **envp, t_set *settings);
void		increment_shlvl(t_env **env);
void		init_ps(t_env **env, t_set *settings);
/*----------------ENV_UTILS----------------*/
void		env_add(t_env *newest, t_env **env);
void		env_del(char *del, t_env **env);
t_env		*env_last(t_env *env);
char		*env_getval(char *key, t_env *env);
char		**env_getval_split(char *key, t_env *env);
void		env_change_val(char *key, char *value, t_env *env, bool is_exp);
void		env_update(char *key, bool is_exported, t_env **env);
t_env		*env_getptr(char *key, t_env *env);
int			env_contain(char *newest, t_env *env);
int			env_isdefined(char *key, t_env *env);
char		**re_char_etoile_etoilise_env(t_env *env);
t_env		*env_new_specific(char *key, char *value, bool is_exported);

/*----------------TO_DELETE_UTILS----------------*/
void		print_char_arr(char **arr);
void		print_cmd(t_command *cmd);

/*----------------MATH----------------*/
bool		is_math(const char *str);
bool		do_math(t_command *cmd, t_env *env);

#endif
