/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:37:31 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/26 17:07:51 by tcharanc         ###   ########.fr       */
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

static int	good_ret(long ret, bool repl)
{
	if (!repl)
		return (ret);
	else if (ret < 0)
		return (ret * (-1));
	else
		return (-1);
}

static long	srch_exec_comm(t_command *cmd, t_env *env, bool only_repl)
{
	bool	repl;
	char	quoted;
	int		start;
	long	ret;

	quoted = '\0';
	start = 0;
	repl = false;
	ret = -1;
	while (cmd->content[start])
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
		}
		start++;
	}
	return (good_ret(ret, repl));
}

long	command_substitution(t_command *cmd, t_env *env, bool only_repl)
{
	t_command	*next;
	bool		skip_first;
	long		ret;

	skip_first = false;
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		if (is_math(cmd->content))
			do_math(cmd, env);
		else if (ft_strchr(cmd->content, '(') && ft_strchr(cmd->content, ')'))
		{
			next = cmd->next;
			ret = srch_exec_comm(cmd, env, only_repl);
			if (ret == 120)
				return (1);
			else if (ret >= 0 && !skip_first)
				skip_first = true;
			cmd = next;
			continue ;
		}
		cmd = cmd->next;
	}
	if (skip_first)
		return (ret);
	else
		return (-1);
}
