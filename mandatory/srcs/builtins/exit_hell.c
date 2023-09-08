/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:15:30 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/08 17:42:54 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

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

int	exit_hell(char **cmd, long ret)
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
			write(2, "exit: ", 6);
			write(2, cmd[1], ft_strlen(cmd[1]));
			write(2, ": numeric argument required\n", 28);
			exit_code = 2;
		}
		else
			exit_code = ft_atol(cmd[1]);
	}
	else
		exit_code = ret;
	exit(exit_code % 256);
}
