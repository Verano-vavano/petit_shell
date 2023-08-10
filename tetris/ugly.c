/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ugly.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 03:02:46 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/04 18:47:24 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

void	i_form(t_map *map)
{
	map->next[0][0] = 'i';
	map->next[0][1] = 'I';
	map->next[0][2] = 'i';
	map->next[0][3] = 'i';
}

void	o_form(t_map *map)
{
	map->next[0][1] = 'o';
	map->next[0][2] = 'O';
	map->next[1][1] = 'o';
	map->next[1][2] = 'o';
}

void	t_form(t_map *map)
{
	map->next[0][0] = 't';
	map->next[0][1] = 'T';
	map->next[0][2] = 't';
	map->next[1][1] = 't';
}

void	l_form(t_map *map, int n)
{
	char	c;

	c = 'l';
	if (n == J_PIECE)
		c = 'j';
	map->next[0][0] = c;
	map->next[0][1] = c + ('A' - 'a');
	map->next[0][2] = c;
	if (n == L_PIECE)
		map->next[1][0] = c;
	else
		map->next[1][2] = c;
}

void	s_form(t_map *map, int n)
{
	char	c;

	c = 's';
	if (n == Z_PIECE)
		c = 'z';
	map->next[0][1] = c + ('A' - 'a');
	map->next[1][1] = c;
	if (n == S_PIECE)
	{
		map->next[0][2] = c;
		map->next[1][0] = c;
	}
	else
	{
		map->next[1][2] = c;
		map->next[0][0] = c;
	}
}
