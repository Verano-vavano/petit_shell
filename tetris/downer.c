/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   downer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 02:36:24 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 14:14:56 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

void	move_down(t_map *map)
{
	int	i;
	int	index;

	i = HEIGHT_BOARD;
	while (i > 0 && map->map[i][ft_strchr_int(map->map[i], 'm')] == 0)
		i--;
	while (i > 0 && (map->map[i][ft_strchr_int(map->map[i], 'm')] != 0
		|| map->map[i][ft_strchr_int(map->map[i], 'M')]))
	{
		while (map->map[i][ft_strchr_int(map->map[i], 'm')] != 0
			|| map->map[i][ft_strchr_int(map->map[i], 'M')] != 0)
		{
			index = ft_strchr_int(map->map[i], 'm');
			if (map->map[i][index] == 0)
				index = ft_strchr_int(map->map[i], 'M');
			map->map[i + 1][index] = map->map[i][index];
			map->map[i][index] = '0';
		}
		i--;
	}
	map->y_pivot++;
}

bool	verif_down(t_map *map)
{
	int	i;
	int	j;

	i = HEIGHT_BOARD;
	while (i > 0 && map->map[i][ft_strchr_int(map->map[i], 'm')] == 0)
		i--;
	while (i > 0 && (map->map[i][ft_strchr_int(map->map[i], 'm')] != 0
		|| map->map[i][ft_strchr_int(map->map[i], 'M')] != 0))
	{
		j = 0;
		while (map->map[i][j])
		{
			if ((map->map[i][j] == 'm' || map->map[i][j] == 'M')
				&& map->map[i + 1][j] != '0' && map->map[i + 1][j] != 'm'
				&& map->map[i + 1][j] != 'M')
				return (false);
			j++;
		}
		i--;
	}
	return (true);
}

static int	add_new_piece(t_map *map)
{
	soft_drop_score(map, false);
	replace_moving(map);
	line_checker(map);
	cpy_piece(map);
	get_next_piece(map);
	draw_next(map);
	if (add_piece(map))
		return (1);
	add_piece(map);
	draw_piece(map, 0);
	tputs(tgoto(map->cm_cap, 0, 0), 1, putchar);
	return (0);
}

int	move_piece(t_map *map)
{
	if (map->actual_declared == false)
	{
		get_next_piece(map);
		cpy_piece(map);
		map->actual_declared = true;
		get_next_piece(map);
		draw_next(map);
		if (add_piece(map))
			return (1);
		draw_piece(map, 0);
		return (0);
	}
	if (verif_down(map))
	{
		draw_piece(map, BLACK);
		move_down(map);
		draw_piece(map, 0);
	}
	else
		return (add_new_piece(map));
	return (0);
}

void	hard_drop(t_map *map)
{
	int	y_start;

	draw_piece(map, BLACK);
	y_start = map->y_pivot;
	while (verif_down(map))
		move_down(map);
	hard_drop_score(map, y_start);
}
