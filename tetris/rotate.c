/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:06:20 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 15:55:41 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static bool	on_place_verif(t_map *map, char side, int x, int y)
{
	if (side == 'l'
		&& ((map->y_pivot + x <= 0 || map->x_pivot - y <= 0)
			|| (map->map[map->y_pivot + x][map->x_pivot - y] != '0'
			&& map->map[map->y_pivot + x][map->x_pivot - y] != 'm')))
		return (false);
	else if (side == 'r'
		&& ((map->y_pivot - x <= 0 || map->x_pivot + y <= 0)
			|| (map->map[map->y_pivot - x][map->x_pivot + y] != '0'
			&& map->map[map->y_pivot - x][map->x_pivot + y] != 'm')))
		return (false);
	return (true);
}

bool	verif_rotate(t_map *map, char side)
{
	int	x;
	int	y;

	if (get_char_map(map->actual) == 'o')
		return (false);
	y = -3;
	if (map->y_pivot < 4)
		y = 1 - map->y_pivot;
	while (y < 3 && map->map[map->y_pivot + y][1] != '1')
	{
		x = -3;
		if (map->x_pivot < 4)
			x = 1 - map->x_pivot;
		while (x < 3 && map->map[1][map->x_pivot + x] != '1')
		{
			if (map->map[map->y_pivot + y][map->x_pivot + x] == 'm'
				&& !(on_place_verif(map, side, x, y)))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

static void	substitute_cpy(t_map *map, char **temp)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			if (temp[i][j] == 'm')
				map->map[map->y_pivot + 3 - i][map->x_pivot + 3 - j] = 'm';
			j++;
		}
		i++;
	}
	free_char_etoile_etoile(temp);
}

static int	get_coord(t_map *map, char c)
{
	if (c == 'y' && map->y_pivot < 4)
		return (1 - map->y_pivot);
	else if (c == 'x' && map->x_pivot < 4)
		return (1 - map->x_pivot);
	return (-3);
}

void	rotate_side(t_map *map, char side)
{
	char	**temp;
	int		x;
	int		y;

	temp = create_temp_arr();
	y = get_coord(map, 'y');
	while (y < 3 && map->map[map->y_pivot + y][1] != '1')
	{
		x = get_coord(map, 'x');
		while (x < 3 && map->map[1][map->x_pivot + x] != '1')
		{
			if (map->map[map->y_pivot + y][map->x_pivot + x] == 'm')
			{
				if (side == 'l')
					temp[3 - x][3 + y] = 'm';
				else
					temp[3 + x][3 - y] = 'm';
				map->map[map->y_pivot + y][map->x_pivot + x] = '0';
			}
			x++;
		}
		y++;
	}
	substitute_cpy(map, temp);
}
