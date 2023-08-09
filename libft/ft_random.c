/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:23:28 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/31 09:48:14 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// requires time and getpid
int	ft_random(void)
{
	static int	i;
	static int	iter;
	long long	n;

	if (i == 0)
		i = ft_getpid() % 50 + 50;
	if (i < 0)
		i = 50;
	n = ft_time();
	if (n == -1)
		return (-1);
	iter = 0;
	while (iter < i)
	{
		n = ((n * 7621) + 1) % INT_MAX;
		iter++;
	}
	i--;
	return (n);
}

/* Generates n so low <= n < high */
int	ft_randint(int low, int high)
{
	return (low + (ft_random() % (high - low)));
}
