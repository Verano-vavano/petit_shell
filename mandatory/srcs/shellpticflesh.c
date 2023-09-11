/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:08:44 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/11 15:55:33 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	g_sig_rec;

static void	assign_vars(t_command *cmd, t_env **env)
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
		if (!env || !(*env))
			*env = env_new(cmd->content, false);
		else
			env_update(cmd->content, false, *env, NULL);
		cmd = cmd->next;
	}
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

static long	exec_loop(t_command *lexed, t_tool *tool, int *hd_no)
{
	long	rt_val;
	bool	start;

	rt_val = tool->rt_val;
	start = true;
	while (lexed && (start
			|| (!ft_strcmp(lexed->content, "&&") && rt_val == 0)
			|| (!ft_strcmp(lexed->content, "||") && rt_val != 0)
			|| (!ft_strcmp(lexed->content, ";"))))
	{
		if (lexed->purpose == CMD_DELIM)
			lexed = lexed->next;
		rt_val = expand_cmd(lexed, tool);
		if (rt_val < 0)
		{
			quote_remove_cmd(lexed);
			rt_val = execute_the_line(lexed, tool, hd_no);
		}
		assign_vars(lexed, &(tool->env));
		while (lexed && lexed->purpose != CMD_DELIM)
			lexed = lexed->next;
		start = false;
		tool->rt_val = rt_val;
	}
	return (rt_val);
}

long	cmd_processing(char *line, t_tool *tool, bool add_line)
{
	t_command	*lexed;
	int			heredoc_no;
	long		rt_val;

	lexed = spliter_init(line, add_line, tool->hist, tool->env);
	if (!lexed)
		return (2);
	else if (!lexed->content)
		return (0);
	rt_val = line_beauty(lexed, tool->env);
	if (rt_val)
		return (rt_val);
	heredoc_no = 0;
	rt_val = exec_loop(lexed, tool, &heredoc_no);
	unlink_heredocs(lexed);
	free_command(lexed);
	free(line);
	return (tool->rt_val);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_tool	tool;

	(void)ac;
	(void)av;
	tool.rt_val = 0;
	tool.env = env_init(envp);
	tool.hist = load_history(tool.env);
	while (42)
	{
		g_sig_rec = 0;
		signal(SIGINT, sig_main);
		signal(SIGQUIT, sig_main);
		line = new_prompt(1, tool.env);
		signal(SIGINT, sig_catch);
		signal(SIGQUIT, sig_catch);
		if (!line)
		{
			printfd(STDOUT_FILENO, "exit\n");
			exit_hell(0, 0);
		}
		else if (!(*line))
			continue ;
		tool.rt_val = cmd_processing(line, &tool, true);
	}
}
