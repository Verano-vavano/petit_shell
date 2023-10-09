/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:08:44 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/09 10:14:16 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "libft.h"

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

static void	get_settings(int ac, char **av, t_set *settings)
{
	int	i;

	i = 0;
	settings->rc = true;
	settings->ps = 2;
	settings->c = 0;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-c") == 0 || ft_strcmp(av[i], "--compute") == 0)
		{
			settings->c = i;
			return ;
		}
		else if (ft_strcmp(av[i], "-n") == 0 || ft_strcmp(av[i], "--norc") == 0)
			settings->rc = false;
		else if (ft_strcmp(av[i], "-p") == 0 || ft_strcmp(av[i], "--nops") == 0)
			settings->ps = 0;
		else if (ft_strcmp(av[i], "-b") == 0 || ft_strcmp(av[i], "--bps") == 0)
			settings->ps = 1;
		else if (ft_strcmp(av[i], "-d") == 0 || !ft_strcmp(av[i], "--debug"))
		{
			settings->rc = false;
			settings->ps = 1;
		}
		i++;
	}
}

static int	init_shell(t_tool *tool, int ac, char **av, char **envp)
{
	int		ret;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)
		|| !isatty(STDERR_FILENO))
		return (1);
	get_settings(ac, av, &(tool->settings));
	tool->rt_val = 0;
	tool->cwd = 0;
	tool->env = env_init(envp, &(tool->settings));
	tool->hist = 0;
	tool->alias_start = 0;
	tool->alias_end = 0;
	if (tool->settings.c)
	{
		ret = cmd_processing(ft_strdup(av[tool->settings.c + 1]), tool, false);
		free_tool(tool);
		return (-1 * (ret == 0) + ret * (ret != 0));
	}
	tool->hist = load_history(tool->env);
	if (tool->settings.rc)
		exec_shellptrc(tool);
	return (0);
}

static int	clean_exit(t_tool tool)
{
	write_hist(tool.hist, tool.env);
	if (tool.cwd)
		free(tool.cwd);
	free_history(tool.hist, true);
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
		return (0 * (ret == -1) + ret * (ret != -1));
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
			exit(clean_exit(tool));
		tool.rt_val = cmd_processing(line, &tool, true);
	}
}
