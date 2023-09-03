/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:23:28 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/04 00:02:06 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Checks RDRAND support
static bool	is_rdrand_sup(void)
{
	bool	result;

	{
		asm (
			"mov $1, %%eax\n"
			"cpuid\n"
			"mov $0, %[result]\n"
			"bt $30, %%ecx\n"
			"setc %[result]\n"
			: [result] "=r" (result)
			:
			: "eax", "ebx", "ecx", "edx"
			);
	}
	return (result);
}

static uint32_t	ft_rdrand(void)
{
	uint32_t	randed;

	{
		asm (
			"rdrand %0\n"
			: "=r" (randed)
			);
	}
	return (randed);
}

// requires time and getpid
static int	ft_custom_random(void)
{
	static int	i;
	int			iter;
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

/* Two random functions :
 * - the first one uses asm instruction RDRAND which is only on Intel CPUs and 
 *   recent AMDs I think ?
 *   I can't really test this, I only have Intel,
 *   so your job Mr tibo le bo if you have AMD
 * - the second one uses the time and the current pid to loop over and over 
 *   with a very peculiar formula
 *   that I found on Stack Overflow of course, which allows it to never
 *   goes beyond INT_MAX but still be
 *   very chelou lol
 * And if the user has a very old AMD CPU that doesn't support
 * either RDRAND or GETPID, well fuck him */
int	ft_random(void)
{
	if (is_rdrand_sup())
		return (ft_rdrand() % INT_MAX);
	else
		return (ft_custom_random());
}

/* Generates n so low <= n < high */
int	ft_randint(int low, int high)
{
	return (low + (ft_random() % (high - low)));
}
