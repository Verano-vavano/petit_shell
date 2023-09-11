/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_des_enfers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:54:37 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/11 15:57:21 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	is_arg(char *arg, int *newline)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	if (arg[i] != '\0')
		return (0);
	*newline = 0;
	return (1);
}

int	echo_des_enfers(char **cmd)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	if (cmd[i])
	{
		while (cmd[i] && is_arg(cmd[i], &newline))
			i++;
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			if (cmd[i + 1])
				printf(" ");
			i++;
		}
	}
	if (newline)
		printf("\n");
	return (0);
}
