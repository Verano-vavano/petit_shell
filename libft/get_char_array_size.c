/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char_etoile_etoile_size.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:07:45 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/13 12:15:26 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_char_array_size(char **char_etoile_etoile)
{
	int i;

	i = 0;
	while(char_etoile_etoile[i])
		i++;
	return (i);
}
