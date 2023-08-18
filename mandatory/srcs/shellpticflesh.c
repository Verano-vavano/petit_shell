/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:08:44 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/18 18:52:25 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	g_sig_rec;

static long	line_exec(t_command *cmd, t_env *env, int *heredoc_no)
{
	quote_remove_cmd(cmd);
	return (execute_the_line(cmd, env, heredoc_no));
}

int	cmd_processing(char *line, t_env *env)
{
	t_command	*lexed;
	t_command	*lexed_cpy;
	int			heredoc_no;
	long		rt_val;

	lexed = spliter_init(line);
	if (!lexed || !(lexed->content) || understand_the_line(lexed)
		|| g_sig_rec || here_doc(lexed))
		return (1);
	lexed_cpy = lexed;
	heredoc_no = 0;
	while (lexed_cpy && (lexed_cpy->purpose == COMMAND
			|| (!ft_strcmp(lexed_cpy->content, "&&") && rt_val == 0)
			|| (!ft_strcmp(lexed_cpy->content, "||") && rt_val != 0)
			|| (!ft_strcmp(lexed_cpy->content, ";"))))
	{
		if (lexed_cpy->purpose == CMD_DELIM)
			lexed_cpy = lexed_cpy->next;
		if (!expand_cmd(lexed_cpy, env))
			rt_val = line_exec(lexed_cpy, env, &heredoc_no);
		else
			rt_val = 1;
		while (lexed_cpy && lexed_cpy->purpose != CMD_DELIM)
			lexed_cpy = lexed_cpy->next;
	}
	print_lexed(lexed);
	unlink_heredocs(lexed);
	free_command(lexed);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	*env;

	(void)ac;
	(void)av;
	g_sig_rec = 0;
	env = env_init(envp);
	while (42)
	{
		signal(SIGINT, sig_main);
		signal(SIGQUIT, sig_main);
		line = readline(PS1);
		signal(SIGINT, sig_catch);
		signal(SIGQUIT, sig_catch);
		if (!line)
		{
			printf("exit\n");
			exit_hell(0);
		}
		else if (!(*line))
			continue ;
		cmd_processing(line, env);
		g_sig_rec = 0;
	}
}
