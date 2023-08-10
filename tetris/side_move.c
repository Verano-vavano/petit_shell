/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:31:33 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 16:01:19 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

bool	verif_side(t_map *map, char side)
{
	int	i;
	int	j;
	int	s;

	i = HEIGHT_BOARD;
	s = 1;
	if (side == 'l')
		s = -1;
	while (i > 0 && map->map[i][ft_strchr_int(map->map[i], 'm')] == 0)
		i--;
	while (i > 0 && (map->map[i][ft_strchr_int(map->map[i], 'm')] != 0
		|| map->map[i][ft_strchr_int(map->map[i], 'M')] != 0))
	{
		j = 0;
		while (map->map[i][j])
		{
			if ((map->map[i][j] == 'm' || map->map[i][j] == 'M')
				&& map->map[i][j + s] != '0' && map->map[i][j + s] != 'm'
				&& map->map[i][j + s] != 'M')
				return (false);
			j++;
		}
		i--;
	}
	return (true);
}

void	move_side(t_map *map, char side)
{
	int	i;
	int	index;
	int	s;

	s = 1 * (side != 'l') + (-1 * (side == 'l'));
	map->x_pivot += s;
	i = HEIGHT_BOARD;
	while (i > 0 && map->map[i][ft_strchr_int(map->map[i], 'm')] == 0)
		i--;
	while (i > 0 && (map->map[i][ft_strchr_int(map->map[i], 'm')] != 0
		|| map->map[i][ft_strchr_int(map->map[i], 'M')] != 0))
	{
		index = 1 * (side != 'r') + (WIDTH_BOARD - 1) * (side == 'r');
		while (map->map[i][index] && index > 0)
		{
			if (map->map[i][index] == 'm' || map->map[i][index] == 'M')
			{
				map->map[i][index + s] = map->map[i][index];
				map->map[i][index] = '0';
			}
			index += (s * (-1));
		}
		i--;
	}
}
