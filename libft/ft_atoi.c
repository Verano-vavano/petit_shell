/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:20:54 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/14 12:59:17 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_spc(char c)
{
	return (c == ' ' || (unsigned)c - '\t' < 5);
}

int	ft_atoi(const char *s)
{
	int	neg;
	int	n;

	neg = 0;
	n = 0;
	while (is_spc(*s))
		s++;
	if (*s == '-')
		neg = 1;
	else if (*s == '+')
		s++;
	while (is_dgt(*s))
		n = n * 10 - (*s++ - '0');
	if (neg)
		return (n);
	else
		return (-n);
}
