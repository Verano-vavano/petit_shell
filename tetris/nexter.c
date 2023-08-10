/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nexter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:13:04 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 15:26:07 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static void	clear_next(t_map *map)
{
	int	l;
	int	i;

	printf("%s", BLACK);
	l = map->fl_next + 1;
	while (l < map->fl_next + 6)
	{
		tputs(tgoto(map->cm_cap, map->fc_next + 2, l), 1, putchar);
		i = -1;
		while (++i < 6)
			printf("%s", SQUARE);
		l++;
	}
	tputs(tgoto(map->cm_cap, 0, 0), 1, putchar);
	printf("\n");
}

void	draw_next(t_map *map)
{
	int	fc;
	int	fl;
	int	i;
	int	j;

	fc = map->fc_next + 4;
	fl = map->fl_next + 3;
	i = -1;
	clear_next(map);
	change_color(get_char_map(map->next));
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (map->next[i][j] != '0')
			{
				tputs(tgoto(map->cm_cap, fc + (j * 2), fl + i), 1, putchar);
				printf("%s", SQUARE);
			}
		}
	}
	printf("%s", WHITE);
	tputs(tgoto(map->cm_cap, 0, 0), 1, putchar);
	printf("\n");
}

void	cpy_piece(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			map->actual[i][j] = map->next[i][j];
			j++;
		}
		i++;
	}
}

static int	get_x_piv(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
			if (ft_isupper(map->actual[y][x]))
				return (x);
	}
	return (0);
}

int	add_piece(t_map *map)
{
	int	x;
	int	x_draw;
	int	y;

	x_draw = ((WIDTH_BOARD + 2) / 2) - get_x_piv(map) - 1;
	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			if (map->actual[y][x] != '0' && map->map[y + 1][x_draw + x] != '0')
				return (1);
			else if (ft_isupper(map->actual[y][x]))
			{
				map->map[y + 1][x_draw + x] = 'M';
				map->x_pivot = x_draw + x;
				map->y_pivot = y + 1;
			}
			else if (map->actual[y][x] != '0')
				map->map[y + 1][x_draw + x] = 'm';
		}
	}
	return (0);
}
