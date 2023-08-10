/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_ftoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:55:49 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 14:56:19 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	len_int(int i)
{
	int	n;

	n = 1;
	while (i > 9)
	{
		i /= 10;
		n++;
	}
	return (n);
}

char	*ft_simple_ftoa(float f, int dec)
{
	int		int_part;
	int		i;
	int		int_len;
	char	*str;

	int_part = (int)f;
	int_len = len_int(int_part);
	str = calloc(int_len + dec + 1, sizeof (char));
	i = int_len;
	if (int_part == 0)
		str[0] = '0';
	while (int_part > 0)
	{
		str[int_len - 1] = int_part % 10 + '0';
		int_part /= 10;
		int_len--;
	}
	str[i] = '.';
	while (dec--)
	{
		f *= 10;
		str[i + 1] = (((int) f) % 10) + '0';
		i++;
	}
	return (str);
}
