/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:08:44 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/01 21:23:44 by hdupire          ###   ########.fr       */
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
			env_update(cmd->content, false, env);
		cmd = cmd->next;
	}
}

static long	line_beauty(t_command *lexed, t_tool *tool)
{
	long	ret;

	if (!lexed || !(lexed->content))
		return (1);
	ret = understand_the_line(lexed);
	if (ret)
		return (ret);
	ret = here_doc(lexed, tool);
	if (ret)
		return (ret);
	return (0);
}

static bool	has_command(t_command *cmd)
{
	while (cmd)
	{
		if (cmd && cmd->content && cmd->content[0] && cmd->purpose == COMMAND)
			return (true);
		cmd = cmd->next;
	}
	return (false);
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
		alias_expansion(lexed, tool);
		rt_val = expand_cmd(lexed, tool);
		quote_remove_cmd(lexed);
		if (rt_val < 0)
		{
			rt_val = 0;
			if (has_command(lexed))
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

	if (!line)
		return (0);
	if (!(*line))
	{
		free(line);
		return (0);
	}
	lexed = spliter_init(&line, add_line, tool);
	free(line);
	if (!lexed)
		return (2);
	else if (!lexed->content)
	{
		free(lexed);
		return (0);
	}
	rt_val = line_beauty(lexed, tool);
	if (rt_val)
		return (rt_val);
	heredoc_no = 0;
	rt_val = exec_loop(lexed, tool, &heredoc_no);
	unlink_heredocs(lexed);
	free_command(lexed);
	return (tool->rt_val);
}

static int	check_exec(int ac, char **av, t_tool *tool)
{
	int	ret;

	av++;
	while (ac > 1)
	{
		if (!ft_strcmp(*av, "-c"))
		{
			ret = 0;
			if (ac >= 2)
				ret = cmd_processing(ft_strdup(av[1]), tool, false);
			free_tool(tool);
			return (-1 * (ret == 0) + ret * (ret != 0));
		}
		ac--;
		av++;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	int		ret;
	bool	exec_rc;
	t_tool	tool;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || !isatty(STDERR_FILENO))
		return (1);
	exec_rc = check_rc(ac, av);
	tool.rt_val = 0;
	tool.cwd = 0;
	tool.env = env_init(envp);
	tool.hist = 0;
	tool.alias_start = 0;
	tool.alias_end = 0;
	ret = check_exec(ac, av, &tool);
	if (ret)
		return (0 * (ret == -1) + ret * (ret != -1));
	tool.hist = load_history(tool.env);
	if (exec_rc)
		exec_shellptrc(&tool);
	while (42)
	{
		g_sig_rec = 0;
		signal(SIGINT, sig_main);
		signal(SIGQUIT, sig_main);
		line = new_prompt(1, &tool);
		if (g_sig_rec == SIGINT)
			tool.rt_val = 130;
		signal(SIGINT, sig_catch);
		signal(SIGQUIT, sig_catch);
		if (!line)
		{
			printfd(STDOUT_FILENO, "exit\n");
			write_hist(tool.hist, tool.env);
			free_history(tool.hist);
			free_whole_env(tool.env);
			free_alias(tool.alias_start);
			exit(tool.rt_val);
		}
		tool.rt_val = cmd_processing(line, &tool, true);
	}
}
