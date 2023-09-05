/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:17:36 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/04 16:31:38 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	*dollar_comprehender(char *arg, t_env *env, int len_key)
{
	size_t	len;
	bool	dollar;
	char	*param;
	char	*param_val;
	char	**temp;

	param_val = 0;
	temp = 0;
	dollar = arg[0] == '#';
	param = ft_strndup(arg + dollar, len_key);
	if (env_contain(param, env))
		temp = env_getval(param, env);
	if (temp)
		param_val = ft_strdup(temp[0]);
	if (dollar)
	{
		len = ft_strlen(param_val);
		free(param);
		return (ft_itoa(len));
	}
	return (param_val);
}

static void	put_param_in(t_command *cmd, int *se, char *to_change, t_env *env)
{
	se[0]--;
	if (to_change && *to_change)
		word_split(cmd, to_change, se, env);
	else
		word_split(cmd, "\0", se, env);
}

static void	parameter_expand_it(t_command *cmd, int i, t_env *env, char quoted)
{
	int		se[2];
	bool	brack;
	char	*arg;
	char	*to_change;
	char	**temp;

	se[0] = i + 1;
	to_change = 0;
	brack = (cmd->content[se[0]] == '{');
	se[1] = find_arg_len(cmd->content + se[0], brack, quoted);
	arg = ft_strndup(cmd->content + se[0] + brack, se[1] - brack);
	to_change = 0;
	if (!brack && env_contain(arg, env))
	{
		temp = env_getval(arg, env);
		if (temp)
			to_change = temp[0];
	}
	else if (brack)
		to_change = dollar_comprehender(arg, env, se[1]);
	se[1] += brack;
	put_param_in(cmd, se, to_change, env);
	free(arg);
	if (brack)
		free(to_change);
}

static void	parameter_seeker(t_command *cmd, t_env *env)
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
			&& quoted != '\'' && cmd->content[i + 1] != '(')
		{
			parameter_expand_it(cmd, i, env, quoted);
			parameter_seeker(cmd, env);
			return ;
		}
		i++;
	}
}

void	parameter_expansion(t_command *cmd, t_env *env)
{
	while (cmd)
	{
		if (ft_strchr(cmd->content, '$'))
			parameter_seeker(cmd, env);
		cmd = cmd->next;
	}
}
