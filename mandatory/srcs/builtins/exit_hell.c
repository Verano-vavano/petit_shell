/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:15:30 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/07 11:07:17 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	exit_hell(char **cmd, long ret)
{
	int	exit_code;
	int	i;

	if (cmd && cmd[1] && cmd[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return (1);
	}
	if (cmd && cmd[1])
	{
		i = 0;
		i += (cmd[1][0] == '+' || cmd[1][0] == '-');
		while (is_dgt(cmd[1][i]))
			i++;
		if (cmd[1][i] != '\0')
		{
			write(2, "exit: ", 6);
			write(2, cmd[1], ft_strlen(cmd[1]));
			write(2, ": numeric argument required\n", 28);
			exit_code = 2;
		}
		else
			exit_code = ft_atoi(cmd[1]);
	}
	else
		exit_code = ret;
	exit(exit_code % 256);
}
