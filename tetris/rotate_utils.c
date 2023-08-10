/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:54:55 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 15:56:20 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

char	**create_temp_arr(void)
{
	char	**temp;
	int		i;

	temp = ft_calloc(9, sizeof (char *));
	if (temp == 0)
		return (0);
	i = 0;
	while (i < 8)
	{
		temp[i] = ft_calloc(9, sizeof (char));
		if (temp[i] == 0)
		{
			free_char_etoile_etoile(temp);
			return (0);
		}
		fill_char_etoile(temp[i], '0', 8);
		i++;
	}
	temp[3][3] = 'M';
	return (temp);
}
