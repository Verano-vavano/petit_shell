/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:25:49 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 15:26:24 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

void	get_next_piece(t_map *map)
{
	int	n;
	int	i;

	n = -1;
	while (n == map->prev || n == -1)
		n = ft_randint(0, 7);
	i = -1;
	while (++i < 4)
		fill_char_etoile(map->next[i], '0', 4);
	if (n == I_PIECE)
		i_form(map);
	else if (n == O_PIECE)
		o_form(map);
	else if (n == T_PIECE)
		t_form(map);
	else if (n == L_PIECE || n == J_PIECE)
		l_form(map, n);
	else
		s_form(map, n);
	tputs(tgoto(map->cm_cap, 0, 0), 1, putchar);
	map->prev = n;
}
