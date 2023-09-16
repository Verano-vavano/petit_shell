/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:17:36 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/17 00:24:47 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	*dollar_comprehender(char *arg, t_env *env, int len_key)
{
	size_t	len;
	bool	dollar;
	char	*param;
	char	*param_val;
	char	*temp;

	param_val = NULL;
	temp = NULL;
	dollar = (arg[0] == '#');
	(void) len_key;
	param = ft_strdup(arg + dollar);
	if (!param)
		return (0);
	if (env_contain(param, env))
		temp = env_getval(param, env);
	param_val = ft_strdup(temp);
	if (dollar && temp && param_val)
	{
		len = ft_strlen(param_val);
		free(param);
		free(param_val);
		return (ft_itoa(len));
	}
	free(param);
	return (param_val);
}

static int	put_param_in(t_command *cmd, int *se, char *to_change, t_env *env)
{
	char	*temp;
	int		ret;

	se[0]--;
	ret = 0;
	if (cmd->purpose == VAR_ASSIGN || cmd->purpose == PS_EXP)
	{
		temp = ft_strreplace(cmd->content, se[0], se[1] + 1, to_change);
		free(cmd->content);
		cmd->content = temp;
	}
	else if (to_change && *to_change)
		ret = word_split(cmd, to_change, se, env);
	else
		ret = word_split(cmd, "\0", se, env);
	free(to_change);
	return (ret);
}

static int	parameter_expand_it(t_command *cmd, int i, t_tool *tool, char q)
{
	int		se[3];
	char	*arg;
	char	*to_change;
	char	*temp;

	to_change = NULL;
	se[0] = i + 1;
	se[2] = (cmd->content[se[0]] == '{');
	se[1] = find_arg_len(cmd->content + se[0], se[2], q);
	arg = ft_strndup(cmd->content + se[0] + se[2], se[1] - se[2]);
	if (!arg)
		return (1);
	if (is_special_param(arg))
		to_change = special_parameter(arg, tool);
	else if (!se[2] && env_contain(arg, tool->env))
	{
		temp = env_getval(arg, tool->env);
		if (temp)
			to_change = ft_strdup(temp);
	}
	else if (se[2])
		to_change = dollar_comprehender(arg, tool->env, se[1]);
	se[1] += se[2];
	free(arg);
	return (put_param_in(cmd, se, to_change, tool->env));
}

static int	parameter_seeker(t_command *cmd, t_tool *tool)
{
	int		i;
	char	quoted;

	i = 0;
	quoted = 0;
	while (cmd->content[i])
	{
		quoted = is_quoted(cmd->content, i, quoted);
		if (cmd->content[i] == '$'
			&& cmd->content[i + 1] && !is_separator(cmd->content[i + 1])
			&& cmd->content[i + 1] != '\'' && cmd->content[i + 1] != '"'
			&& quoted != '\'' && cmd->content[i + 1] != '(')
		{
			if (parameter_expand_it(cmd, i, tool, quoted))
				return (1);
			return (parameter_seeker(cmd, tool));
		}
		i++;
	}
	return (0);
}

int	parameter_expansion(t_command *cmd, t_tool *tool)
{
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		if (ft_strchr(cmd->content, '$'))
		{
			if (parameter_seeker(cmd, tool))
				return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}
