/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_exp_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 23:11:51 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/12 17:43:13 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	find_arg_len(char *s, bool brack, char quoted)
{
	int	i;

	i = 0;
	if (!brack && (s[0] == '?' || s[0] == '0' || s[0] == '$'))
		return (1);
	while (s[i])
	{
		if (!brack && (s[i] < '0' || s[i] > '9') && (s[i] < 'a' || s[i] > 'z')
			&& (s[i] < 'A' || s[i] > 'Z') && s[i] != '_')
			break ;
		else if (!brack && s[i] == quoted)
			break ;
		else if (brack && s[i] == '}')
			break ;
		i++;
	}
	return (i);
}

bool	is_special_param(char *arg)
{
	if (arg[0] == '#')
		arg++;
	return (arg[0] == '?' || arg[0] == '0' || arg[0] == '$');
}

static char	*param_good_ret(char *temp, bool take_len)
{
	int	len;

	if (!take_len)
		return (temp);
	len = ft_strlen(temp);
	free(temp);
	return (ft_itoa(len));
}

char	*special_parameter(char *arg, t_tool *tool)
{
	bool	take_len;
	char	*temp;
	char	*ret;

	take_len = (arg[0] == '#');
	arg += take_len;
	temp = NULL;
	if (arg[0] == '0')
		return (param_good_ret(ft_strdup(SHELL_NAME), take_len));
	else if (arg[0] == '$' && ft_strcmp(OS, "darwin") != 0)
		temp = ft_ltoa(ft_getpid());
	else if (arg[0] == '?')
		temp = ft_itoa(tool->rt_val);
	ret = param_good_ret(temp, take_len);
	return (ret);
}

char	*backslash_it(char *p)
{
	int		i;
	char	*newer;

	i = 0;
	while (p[i])
	{
		newer = 0;
		if (p[i] == '\\')
			newer = ft_strreplace(p, i, 1, "\\\\");
		else if (p[i] == '"')
			newer = ft_strreplace(p, i, 1, "\\\"");
		else if (p[i] == '\'')
			newer = ft_strreplace(p, i, 1, "\\'");
		else if (p[i] == '$')
			newer = ft_strreplace(p, i, 1, "\\$");
		else
			i--;
		if (newer)
		{
			free(p);
			p = newer;
		}
		i += 2;
	}
	return (p);
}
