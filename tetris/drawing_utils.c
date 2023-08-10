/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:03:10 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 14:47:28 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static bool	draw_piece_part(t_map *map, int i, int j)
{
	if (map->map[i][j] == 'm' || map->map[i][j] == 'M')
	{
		tputs(tgoto(map->cm_cap, (map->fc_map + 2) + (j * 2) - 2,
				map->fl_map + i), 1, putchar);
		printf("%s", SQUARE);
		return (true);
	}
	return (false);
}

void	draw_piece(t_map *map, char *color)
{
	int		i;
	int		j;
	bool	one_found;
	bool	old_found;

	old_found = false;
	if (color == 0)
		change_color(get_char_map(map->actual));
	else
		printf("%s", color);
	i = -1;
	while (map->map[++i])
	{
		one_found = false;
		j = -1;
		while (map->map[i][++j])
			one_found = draw_piece_part(map, i, j);
		if ((!one_found) && old_found)
			break ;
		old_found = one_found;
	}
	tputs(tgoto(map->cm_cap, 0, 0), 1, putchar);
	printf("\n");
}

char	get_char_map(char s[4][4])
{
	int		i;

	i = -1;
	while (++i < 4)
		if (s[0][i] != '0')
			return (ft_tolower(s[0][i]));
	return (0);
}

void	change_color(char color)
{
	if (color == 'i')
		printf("%s", I_COLOR);
	else if (color == 'o')
		printf("%s", O_COLOR);
	else if (color == 't')
		printf("%s", T_COLOR);
	else if (color == 'l')
		printf("%s", L_COLOR);
	else if (color == 'j')
		printf("%s", J_COLOR);
	else if (color == 's')
		printf("%s", S_COLOR);
	else if (color == 'z')
		printf("%s", Z_COLOR);
	else if (color == '0')
		printf("%s", BLACK);
}

void	replace_moving(t_map *map)
{
	int		i;
	int		index;
	char	c;

	i = HEIGHT_BOARD;
	c = get_char_map(map->actual);
	while (i > 0 && map->map[i][ft_strchr_int(map->map[i], 'm')] == 0)
		i--;
	while (i > 0 && (map->map[i][ft_strchr_int(map->map[i], 'm')] != 0
		|| map->map[i][ft_strchr_int(map->map[i], 'M')] != 0))
	{
		while (map->map[i][ft_strchr_int(map->map[i], 'm')] != 0
			|| map->map[i][ft_strchr_int(map->map[i], 'M')] != 0)
		{
			index = ft_strchr_int(map->map[i], 'm');
			if (map->map[i][index] == 0)
				index = ft_strchr_int(map->map[i], 'M');
			map->map[i][index] = c;
		}
		i--;
	}
}
