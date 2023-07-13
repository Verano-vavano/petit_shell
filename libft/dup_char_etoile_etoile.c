/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_char_etoile_etoile.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:12:18 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/13 12:17:28 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**dup_char_etoile_etoile(char **char_etoile_etoile)
{
	char **new_arr;
	int i;

	new_arr = malloc(sizeof(char *) * get_char_array_size(char_etoile_etoile));
	return (new_arr);
}
