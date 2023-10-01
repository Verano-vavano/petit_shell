/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 02:52:37 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/01 03:34:08 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hexa_len(long l)
{
	int	len;

	len = 0;
	if (l == 0)
		return (1);
	while (l)
	{
		l /= 16;
		len++;
	}
	return (len);
}

static char	hexa_eq(char n, bool maj)
{
	if (n < 10)
		return ('0' + n);
	else if (maj)
		return ('A' + n - 10);
	else
		return ('a' + n - 10);
}

char	*hexa(long l, bool maj)
{
	char			*hexaed;
	unsigned long	new_l;
	int				i;

	new_l = l;
	if (l < 0)
	{
		i = 16;
		new_l = ULONG_MAX + l + 1;
	}
	else
		i = hexa_len(new_l);
	hexaed = ft_calloc(i + 1, sizeof (char));
	if (!hexaed)
		return (0);
	i--;
	while (i >= 0)
	{
		hexaed[i] = hexa_eq(new_l % 16, maj);
		new_l /= 16;
		i--;
	}
	return (hexaed);
}
