/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_outside.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:35:03 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 19:06:36 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void	draw_next_square(t_map *map)
{
	int	l;
	int	c;

	tputs(tgoto(map->cm_cap, map->fc_next + 6, map->fl_next - 2), 1, putchar);
	printf("NEXT");
	l = 0;
	while (l < 7)
	{
		c = 0;
		tputs(tgoto(map->cm_cap, map->fc_next, map->fl_next + l), 1, putchar);
		if (l == 0 || l == 6)
			while (c++ < 8)
				printf("%s", SQUARE);
		else
		{
			printf("%s", SQUARE);
			tputs(tgoto(map->cm_cap, map->fc_next + 14, map->fl_next + l),
				1, putchar);
			printf("%s", SQUARE);
		}
		l++;
	}
}

static void	draw_square(t_map *map)
{
	int		l;
	int		c;

	l = 0;
	while (l < HEIGHT_BOARD + 2)
	{
		c = 0;
		tputs(tgoto(map->cm_cap, map->fc_map, map->fl_map + l), 1, putchar);
		if (l == 0 || l == HEIGHT_BOARD + 1)
			while (c++ < WIDTH_BOARD + 2)
				printf("%s", SQUARE);
		else
		{
			printf("%s", SQUARE);
			c++;
			printf("%s", BLACK);
			while (c++ < WIDTH_BOARD + 1)
				printf("%s", SQUARE);
			printf("%s%s", WHITE, SQUARE);
		}
		l++;
	}
}

void	draw_outside(t_map *map)
{
	map->cm_cap = tgetstr("cm", NULL);
	printf("%s", WHITE);
	draw_square(map);
	map->fl_next = map->fl_map + ((HEIGHT_BOARD + 2) / 2) - 7;
	map->fc_next = map->fc_map + ((WIDTH_BOARD + 2) * 2) + 4;
	draw_next_square(map);
	tputs(tgoto(map->cm_cap, map->fc_map + WIDTH_BOARD - 1, 0), 1, putchar);
	printf("TETRIS");
	tputs(tgoto(map->cm_cap, 0, 3), 1, putchar);
	printf("\tSCORE = 0\n\n\n\n\tLEVEL = 0\n");
}
