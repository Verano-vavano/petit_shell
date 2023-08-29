/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:08:44 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/29 19:24:16 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	g_sig_rec;

static void	assign_vars(t_command *cmd, t_env *env)
{
	bool		one;
	t_command	*cpy;

	one = true;
	cpy = cmd;
	while (cpy && cpy->purpose != CMD_DELIM)
	{
		if (cpy->purpose == DELIM)
			one = false;
		cpy = cpy->next;
	}
	if (!one)
		return ;
	while (cmd && cmd->purpose == VAR_ASSIGN)
	{
		env_update(cmd->content, false, env, NULL);
		cmd = cmd->next;
	}
}

static long	line_exec(t_command *cmd, t_env *env, t_hist *hist, int *heredoc_no)
{
	quote_remove_cmd(cmd);
	return (execute_the_line(cmd, env, hist, heredoc_no));
}

long	cmd_processing(char *line, t_env *env, t_hist *hist, bool add_line)
{
	t_command	*lexed;
	t_command	*lexed_cpy;
	bool		start;
	int			heredoc_no;
	long		rt_val;

	lexed = spliter_init(line, add_line, hist, env);
	if (!lexed || !(lexed->content) || understand_the_line(lexed)
		|| g_sig_rec || here_doc(lexed, env))
		return (1);
	lexed_cpy = lexed;
	heredoc_no = 0;
	start = true;
	rt_val = 0;
	while (lexed_cpy && (start
			|| (!ft_strcmp(lexed_cpy->content, "&&") && rt_val == 0)
			|| (!ft_strcmp(lexed_cpy->content, "||") && rt_val != 0)
			|| (!ft_strcmp(lexed_cpy->content, ";"))))
	{
		if (lexed_cpy->purpose == CMD_DELIM)
			lexed_cpy = lexed_cpy->next;
		rt_val = expand_cmd(lexed_cpy, env);
		if (rt_val < 0)
			rt_val = line_exec(lexed_cpy, env, hist, &heredoc_no);
		assign_vars(lexed_cpy, env);
		while (lexed_cpy && lexed_cpy->purpose != CMD_DELIM)
			lexed_cpy = lexed_cpy->next;
		start = false;
	}
	//print_lexed(lexed);
	unlink_heredocs(lexed);
	free_command(lexed);
	return (rt_val);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	*env;
	t_hist	*hist;
	long	ret;

	(void)ac;
	(void)av;
	g_sig_rec = 0;
	ret = 0;
	env = env_init(envp);
	hist = load_history(env);
	while (42)
	{
		signal(SIGINT, sig_main);
		signal(SIGQUIT, sig_main);
		line = new_prompt(1, env);
		signal(SIGINT, sig_catch);
		signal(SIGQUIT, sig_catch);
		if (!line)
		{
			printf("exit\n");
			exit_hell(0);
		}
		else if (!(*line))
			continue ;
		ret = cmd_processing(line, env, hist, true);
		g_sig_rec = 0;
	}
	printf("%ld\n", ret);
}
