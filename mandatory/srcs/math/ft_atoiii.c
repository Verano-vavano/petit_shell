/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoiii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:48:30 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/08 17:49:27 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// un mega atoi
#include "math.h"
#include <stdint.h>

intmax_t	ft_atoiii(const char *str)
{
	int				neg;
	intmax_t		num;
	unsigned long	i;

	i = 0;
	neg = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + str[i] - '0';
		i++;
	}
	return (num * neg);
}
