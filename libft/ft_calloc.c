/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:54:07 by hdupire           #+#    #+#             */
/*   Updated: 2023/03/30 11:33:01 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t				i;
	void				*pointeur;

	if (size != 0 && count > SIZE_MAX / size)
		return (0);
	pointeur = malloc(size * count);
	if (pointeur == 0)
		return (pointeur);
	i = 0;
	while (i < count * size)
	{
		*(unsigned char *)(pointeur + i) = 0;
		i++;
	}
	return (pointeur);
}
