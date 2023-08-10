/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:52:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 15:05:12 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static int	down_line(t_map *map, int index)
{
	int	to_down;

	to_down = index - 1;
	while (to_down > 0 && !line_not_zero(map->map[to_down]))
		to_down--;
	if (to_down == 0)
		return (0);
	swap_lines(map->map[index], map->map[to_down]);
	return (to_down);
}

static void	redraw_line(t_map *map, int index)
{
	int		i;
	char	last;

	i = 1;
	tputs(tgoto(map->cm_cap, map->fc_map + 2, map->fl_map + index), 1, putchar);
	last = 0;
	while (map->map[index][i] && map->map[index][i] != '1')
	{
		if (map->map[index][i] != last)
			change_color(map->map[index][i]);
		last = map->map[index][i];
		printf("%s", SQUARE);
		i++;
	}
	tputs(tgoto(map->cm_cap, 0, 0), 1, putchar);
	printf("\n");
}

static void	apply_gravity(t_map *map)
{
	int	index;
	int	changed;

	index = HEIGHT_BOARD;
	while (index > 0)
	{
		if (!line_not_zero(map->map[index]))
		{
			changed = down_line(map, index);
			redraw_line(map, index);
			redraw_line(map, changed);
		}
		index--;
	}
	changed = 1;
}

void	line_checker(t_map *map)
{
	int		index;
	int		num_of_lines;
	bool	destroyed;

	num_of_lines = 0;
	destroyed = false;
	index = HEIGHT_BOARD;
	while (index > 0 && line_not_zero(map->map[index]))
	{
		if (is_line_full(map->map[index]))
		{
			destroyed = true;
			empty_line(map->map[index]);
			num_of_lines++;
		}
		index--;
	}
	if (destroyed)
		apply_gravity(map);
	if (num_of_lines > 0)
	{
		update_score(map, num_of_lines);
		update_level(map, num_of_lines);
	}
	return ;
}
