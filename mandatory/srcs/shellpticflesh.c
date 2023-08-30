/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:08:44 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/30 16:37:29 by hdupire          ###   ########.fr       */
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

static long	line_exec(t_command *cmd, t_tools *tools, int *heredoc_no)
{
	quote_remove_cmd(cmd);
	return (execute_the_line(cmd, tools, heredoc_no));
}

static long	line_beauty(t_command *lexed, t_env *env)
{
	long	ret;

	if (!lexed || !(lexed->content))
	   return (1);
	ret = understand_the_line(lexed);
	if (ret)
		return (ret);
	ret = here_doc(lexed, env);
	if (ret)
		return (ret);
	return (0);
}

long	cmd_processing(char *line, t_tools *tools, bool add_line)
{
	t_command	*lexed;
	t_command	*lexed_cpy;
	bool		start;
	int			heredoc_no;
	long		rt_val;

	lexed = spliter_init(line, add_line, tools->hist, tools->env);
	rt_val = line_beauty(lexed, tools->env);
	if (rt_val)
		return (rt_val);
	lexed_cpy = lexed;
	heredoc_no = 0;
	start = true;
	rt_val = tools->rt_val;
	while (lexed_cpy && (start
			|| (!ft_strcmp(lexed_cpy->content, "&&") && rt_val == 0)
			|| (!ft_strcmp(lexed_cpy->content, "||") && rt_val != 0)
			|| (!ft_strcmp(lexed_cpy->content, ";"))))
	{
		if (lexed_cpy->purpose == CMD_DELIM)
			lexed_cpy = lexed_cpy->next;
		rt_val = expand_cmd(lexed_cpy, tools);
		if (rt_val < 0)
			rt_val = line_exec(lexed_cpy, tools, &heredoc_no);
		assign_vars(lexed_cpy, tools->env);
		while (lexed_cpy && lexed_cpy->purpose != CMD_DELIM)
			lexed_cpy = lexed_cpy->next;
		start = false;
		tools->rt_val = rt_val;
	}
	//print_lexed(lexed);
	unlink_heredocs(lexed);
	free_command(lexed);
	return (rt_val);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_tools	tools;

	(void)ac;
	(void)av;
	tools.rt_val = 0;
	tools.env = env_init(envp);
	tools.hist = load_history(tools.env);
	while (42)
	{
		g_sig_rec = 0;
		signal(SIGINT, sig_main);
		signal(SIGQUIT, sig_main);
		line = new_prompt(1, tools.env);
		signal(SIGINT, sig_catch);
		signal(SIGQUIT, sig_catch);
		if (!line)
		{
			printf("exit\n");
			exit_hell(0, 0);
		}
		else if (!(*line))
			continue ;
		tools.rt_val = cmd_processing(line, &tools, true);
		g_sig_rec = 0;
	}
}
