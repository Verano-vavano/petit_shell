/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scoring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 10:25:20 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 13:43:44 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void	update_screen_score(t_map *map)
{
	tputs(tgoto(map->cm_cap, 0, 3), 1, putchar);
	printf("%s\tSCORE = %lu\n", WHITE, map->score);
}

void	hard_drop_score(t_map *map, int y_start)
{
	int	to_add;

	to_add = soft_drop_score(map, true) * (map->y_pivot - y_start);
	if (map->score > ULONG_MAX - to_add)
		map->score = ULONG_MAX;
	else
		map->score += to_add;
	update_screen_score(map);
}

int	soft_drop_score(t_map *map, bool return_it)
{
	int	to_add;

	to_add = 4 * (map->level + 1);
	if (return_it)
		return (to_add);
	if (map->score > ULONG_MAX - to_add)
		map->score = ULONG_MAX;
	else
		map->score += to_add;
	update_screen_score(map);
	return (to_add);
}

void	update_score(t_map *map, int l)
{
	int	mult;
	int	to_add;

	mult = 40;
	if (l == 2)
		mult = 100;
	else if (l == 3)
		mult = 300;
	else if (l == 4)
		mult = 1200;
	to_add = (mult * (map->level + 1));
	if (map->score > ULONG_MAX - to_add)
		map->score = ULONG_MAX;
	else
		map->score += to_add;
	update_screen_score(map);
}
