/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:17:36 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/29 15:52:45 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"

static int	find_arg_len(char *s, bool brack, char quoted)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!brack && (is_separator(s[i]) || s[i] == '-' || s[i] == ':'))
			break ;
		else if (!brack && s[i] == quoted)
			break ;
		else if (brack && s[i] == '}')
			break ;
		i++;
	}
	return (i);
}

static char	*dollar_comprehender(char *arg, t_env *env, int len_key)
{
	size_t	len;
	bool	dollar;
	char	*param;
	char	*param_val;
	char	*operator;
	char	*replacor;
	char	**temp;

	operator = 0;
	replacor = 0;
	param_val = 0;
	temp = 0;
	if (arg[0] == '#')
	{
		dollar = true;
		arg++;
	}
	param = ft_strndup(arg, len_key);
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
	(void) operator;
	(void) replacor;
	return (param_val);
}

static void	parameter_expand_it(t_command *cmd, int i, t_env *env, char quoted)
{
	int		len;
	bool	brack;
	char	*arg;
	char	*to_change;
	char	**temp;

	i++;
	to_change = 0;
	brack = (cmd->content[i] == '{');
	len = find_arg_len(cmd->content + i, brack, quoted);
	arg = ft_strndup(cmd->content + i + brack, len - brack);
	to_change = 0;
	if (!brack)
	{
		if (env_contain(arg, env))
		{
			temp = env_getval(arg, env);
			if (temp)
				to_change = temp[0];
		}
	}
	else
		to_change = dollar_comprehender(arg, env, len);
	if (to_change && *to_change)
	{
		cmd->content = ft_strreplace(cmd->content, i - 1, len + 1 + brack, to_change);
	}
	else
		cmd->content = ft_strreplace(cmd->content, i - 1, len + 1 + brack, "\0");
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
		if (cmd->content[i] == '$' && quoted != '\'' && cmd->content[i + 1] != '(')
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
