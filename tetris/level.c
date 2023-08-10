/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 11:41:41 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 11:52:11 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void	update_screen_level(t_map *map)
{
	tputs(tgoto(map->cm_cap, 0, 7), 11, putchar);
	printf("\tLEVEL = %d\n", map->level);
}

void	update_level(t_map *map, int l)
{
	map->lines_destroyed += l;
	if (map->lines_destroyed != 0
		&& map->lines_destroyed > (2 * (map->level + 1)))
	{
		map->level++;
		map->lines_destroyed -= (2 * map->level + 2);
		update_screen_level(map);
	}
}
