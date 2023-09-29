/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_des_enfers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:54:37 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/29 21:31:25 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	is_arg(char *arg, bool *newline, bool *escape)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] == 'n' || arg[i] == 'e' || arg[i] == 'E')
	{
		if (*newline && arg[i] == 'n')
			*newline = 0;
		if (*escape && arg[i] == 'E')
			*escape = 0;
		if (!(*escape) && arg[i] == 'e')
			*escape = 1;
		i++;
	}
	if (arg[i] != '\0')
		return (0);
	return (1);
}

static void	echo_arg(char *cmd, bool escape)
{
	char	*temp;
	bool	first;
	int		i;

	first = true;
	if (escape)
	{
		i = 0;
		while (cmd[i])
		{
			if (cmd[i] == '\\' && cmd[i + 1])
			{
				temp = replace_escaped(cmd, i);
				if (temp)
				{
					if (!first)
						free(cmd);
					cmd = temp;
					first = false;
				}
			}
			i++;
		}
	}
	printf("%s", cmd);
}

int	echo_des_enfers(char **cmd)
{
	bool	newline;
	bool	escape;
	int		i;

	newline = 1;
	escape = 0;
	i = 1;
	if (cmd[i])
	{
		while (cmd[i] && is_arg(cmd[i], &newline, &escape))
			i++;
		while (cmd[i])
		{
			echo_arg(cmd[i], escape);
			if (cmd[i + 1])
				printf(" ");
			i++;
		}
	}
	if (newline)
		printf("\n");
	return (0);
}
