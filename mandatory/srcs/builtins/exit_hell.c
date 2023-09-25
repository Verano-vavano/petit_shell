/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:15:30 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/24 16:50:52 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static bool	loop_check(char *s, char *l, bool neg)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (l[i + neg] > s[i])
			return (true);
		else if (l[i + neg] < s[i])
			return (false);
		i++;
	}
	return (true);
}

static bool	str_not_long(char *s)
{
	bool	neg;
	char	*l;
	int		i;

	neg = (s[0] == '-');
	s += (s[0] == '+' || s[0] == '-');
	i = 0;
	while (is_dgt(s[i]))
		i++;
	if (s[i] != '\0')
		return (false);
	if ((int) ft_strlen(s) > ft_longlen(LONG_MAX))
		return (false);
	if (neg)
		l = ft_ltoa(LONG_MIN);
	else
		l = ft_ltoa(LONG_MAX);
	if (!l)
		return (false);
	return (loop_check(s, l, neg));
}

int	exit_hell(char **cmd, long ret, t_tool *tool, bool one)
{
	long	exit_code;

	if (cmd && cmd[1] && cmd[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return (1);
	}
	if (cmd && cmd[1])
	{
		if (!str_not_long(cmd[1]))
		{
			printfd(ERR, "exit: %s: numeric argument required\n", cmd[1]);
			exit_code = 2;
		}
		else
			exit_code = ft_atol(cmd[1]);
	}
	else
		exit_code = ret;
	if (one && tool->c_env)
		free_char_etoile_etoile(tool->c_env);
	if (one && tool->cwd)
		free(tool->cwd);
	free_whole_env(tool->env);
	exit(exit_code % 256);
}
