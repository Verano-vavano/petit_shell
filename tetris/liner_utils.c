/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liner_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:00:30 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 15:06:59 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

bool	line_not_zero(char *map)
{
	int	i;

	i = 1;
	while (map[i] != '1' && map[i])
	{
		if (map[i] != '0')
			return (true);
		i++;
	}
	return (false);
}

bool	is_line_full(char *line)
{
	int	i;

	i = 1;
	while (line[i] != '1' && line[i])
	{
		if (line[i] == '0')
			return (false);
		i++;
	}
	return (true);
}

void	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			line[i] = '0';
		i++;
	}
}

void	swap_lines(char *l1, char *l2)
{
	int		i;
	char	temp;

	i = 0;
	while (l1[i])
	{
		temp = l1[i];
		l1[i] = l2[i];
		l2[i] = temp;
		i++;
	}
}
