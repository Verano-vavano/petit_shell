/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 22:22:39 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 14:59:26 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

void	perform_move(t_map *map, char c)
{
	draw_piece(map, BLACK);
	if (c == 's' && verif_down(map))
		move_down(map);
	else if (c == 'q' && verif_side(map, 'l'))
		move_side(map, 'l');
	else if (c == 'd' && verif_side(map, 'r'))
		move_side(map, 'r');
	else if (c == 'a' && verif_rotate(map, 'l'))
		rotate_side(map, 'l');
	else if (c == 'e' && verif_rotate(map, 'r'))
		rotate_side(map, 'r');
	else if (c == 'x')
		hard_drop(map);
	draw_piece(map, 0);
}
