/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:37:31 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/05 12:57:23 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	find_end_comm(char *s)
{
	int		i;
	int		inside;
	char	quoted;

	i = 1;
	inside = 0;
	quoted = 0;
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

static int	command_it(char *cmd_sent, int *se, t_command *cmd, t_env *env)
{
	t_tool	*empty_tool;
	char	*out;
	int		ret;

	empty_tool = ft_calloc(1, sizeof (t_tool));
	if (!empty_tool)
		return (1);
	empty_tool->env = env;
	ret = 1;
	if (cmd_sent)
		ret = cmd_processing(cmd_sent, empty_tool, false);
	free(cmd_sent);
	printf("\n");
	free(empty_tool);
	if (se[2])
	{
		dup2(se[3], STDOUT_FILENO);
		out = get_output(se + 4);
		if (out && *out)
			word_split(cmd, out, se, env);
		else
			word_split(cmd, "\0", se, env);
		if (out)
			free(out);
	}
	return (ret);
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

static long	srch_exec_comm(t_command *cmd, t_env *env)
{
	bool	repl;
	char	quoted;
	int		start;
	long	ret;

	quoted = 0;
	start = 0;
	repl = false;
	ret = -1;
	while (cmd->content[start])
	{
		quoted = is_quoted(cmd->content, start, quoted);
		if (cmd->content[start] == '(' && quoted != '\'')
		{
			if (start != 0 && cmd->content[start - 1] == '$')
				repl = true;
			ret = perform_exec(cmd, env, start, repl);
		}
		start++;
	}
	if (!repl)
		return (ret);
	else
		return (-1);
}

long	command_substitution(t_command *cmd, t_env *env)
{
	t_command	*next;
	bool		skip_first;
	long		ret;

	skip_first = false;
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		if (ft_strchr(cmd->content, '(') && ft_strchr(cmd->content, ')'))
		{
			next = cmd->next;
			ret = srch_exec_comm(cmd, env);
			if (ret >= 0 && !skip_first)
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
