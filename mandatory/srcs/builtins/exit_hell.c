/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:15:30 by tcharanc          #+#    #+#             */
/*   Updated: 2023/08/10 18:14:47 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	exit_hell(char **cmd)
{
	int	exit_code;
	int	i;

	if (cmd && cmd[1])
	{
		i = 0;
		while (is_dgt(cmd[1][i]))
			i++;
		if (cmd[1][i] != '\0')
		{
			printf("%s: exit: %s: numeric argument required\n",
				"Minishell", cmd[1]);
			exit_code = 255;
		}
		else
			exit_code = ft_atol(cmd[1]);
	}
	else
		exit_code = 0;
	exit(exit_code % 256);
}
