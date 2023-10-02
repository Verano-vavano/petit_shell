/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:08:44 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/02 23:10:26 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	g_sig_rec;

long	cmd_processing(char *line, t_tool *tool, bool add_line)
{
	t_command	*lexed;
	int			heredoc_no;
	long		rt_val;

	if (!line || !(*line))
	{
		if (line)
			free(line);
		return (0);
	}
	lexed = spliter_init(&line, add_line, tool);
	free(line);
	if (!lexed)
		return (2);
	if (!lexed->content)
	{
		free(lexed);
		return (0);
	}
	rt_val = line_beauty(lexed, tool);
	if (rt_val)
		return (rt_val);
	heredoc_no = 0;
	rt_val = exec_loop(lexed, tool, &heredoc_no);
	return (exit_processing(lexed, tool->rt_val));
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

static int	init_shell(t_tool *tool, int ac, char **av, char **envp)
{
	bool	exec_rc;
	int		ret;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)
		|| !isatty(STDERR_FILENO))
		return (1);
	exec_rc = check_rc(ac, av);
	tool->rt_val = 0;
	tool->cwd = 0;
	tool->env = env_init(envp);
	tool->hist = 0;
	tool->alias_start = 0;
	tool->alias_end = 0;
	ret = check_exec(ac, av, tool);
	if (ret)
		return (0 * (ret == -1) + ret * (ret != -1));
	tool->hist = load_history(tool->env);
	if (exec_rc)
		exec_shellptrc(tool);
	return (0);
}

static int	clean_exit(t_tool tool)
{
	write_hist(tool.hist, tool.env);
	if (tool.cwd)
		free(tool.cwd);
	free_history(tool.hist);
	free_whole_env(tool.env);
	free_alias(tool.alias_start);
	return (tool.rt_val);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	int		ret;
	t_tool	tool;

	ret = init_shell(&tool, ac, av, envp);
	if (ret)
		return (ret);
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
			exit(clean_exit(tool));
		}
		tool.rt_val = cmd_processing(line, &tool, true);
	}
}
