/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:37:31 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/27 15:20:32 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include <unistd.h>

static int	find_end_comm(char *s)
{
	int		i;
	int		inside;
	char	quoted;

	i = 1;
	inside = '\0';
	quoted = '\0';
	while (s[i])
	{
		quoted = is_quoted(s, i, quoted);
		if (s[i] == '(' && quoted != '\'')
			inside++;
		else if (s[i] == ')' && quoted != '\'' && !inside)
			return (i);
		else if (s[i] == ')' && quoted != '\'')
			inside--;
		i++;
	}
	return (i);
}

static long	perform_exec(t_command *cmd, t_env *env, int start, bool repl)
{
	int		se[6];
	char	*cmd_sent;

	se[0] = start - repl;
	se[1] = find_end_comm(cmd->content + start) + repl;
	if (repl)
	{
		if (pipe(se + 4) == -1)
			return (1);
		se[3] = dup(STDOUT_FILENO);
		if (dup2(se[5], STDOUT_FILENO) == -1)
		{
			dup2(STDOUT_FILENO, se[3]);
			return (1);
		}
	}
	cmd_sent = ft_strndup(cmd->content + se[0] + repl + 1, se[1] - 1 - repl);
	se[2] = repl;
	return (command_it(cmd_sent, se, cmd, env));
}

static int	good_ret(long ret, bool repl, bool *skip_first)
{
	if (!repl)
	{
		if (ret >= 0)
			*skip_first = true;
		return (ret);
	}
	else if (ret < 0)
	{
		*skip_first = true;
		return (ret * (-1));
	}
	else
		return (-1);
}

static long	srch_exec_comm(t_command *cmd, t_env *env, bool only_repl, bool *sf)
{
	bool	repl;
	char	quoted;
	int		start;
	long	ret;

	quoted = '\0';
	start = -1;
	repl = false;
	ret = -1;
	while (cmd && cmd->content && cmd->content[++start])
	{
		quoted = is_quoted(cmd->content, start, quoted);
		if (cmd->content[start] == '(' && (!quoted
				|| (quoted != '\'' && start && cmd->content[start - 1] == '$')))
		{
			repl = (start != 0 && cmd->content[start - 1] == '$');
			if (!repl && only_repl)
				return (-1);
			ret = perform_exec(cmd, env, start, repl);
			if (ret)
				break ;
			start = -1;
		}
	}
	return (good_ret(ret, repl, sf));
}

long	command_substitution(t_command *cmd, t_env *env, bool only_repl, long r)
{
	t_command	*next;
	bool		skip_first;
	char		**old;

	skip_first = false;
	signal(SIGINT, SIG_DFL);
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		next = cmd->next;
		old = &(cmd->content);
		if (is_math(cmd->content))
		{
			if (!do_math(cmd))
				return (1);
			else if (&(cmd->content) == old)
				continue ;
		}
		else if (ft_strchr(cmd->content, '(') && ft_strchr(cmd->content, ')'))
		{
			r = srch_exec_comm(cmd, env, only_repl, &skip_first);
			if (r == 120)
				return (1);
		}
		cmd = next;
	}
	return (r * skip_first + (-1) * !skip_first);
}
