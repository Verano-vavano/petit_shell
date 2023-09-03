/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:44:02 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/03 23:59:45 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_spc(char c)
{
	return (c == ' ' || (unsigned)c - '\t' < 5);
}

long	ft_atol(const char *s)
{
	long	n;
	int		neg;

	n = 0;
	neg = 1;
	while (is_spc(*s))
		s++;
	if (*s == '-')
		neg = 1;
	else if (*s == '+')
		s++;
	while (is_dgt(*s))
		n = n * 10 - (*s++ - '0');
	if (neg)
		return (-n);
	return (n);
}
