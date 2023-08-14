/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:45:15 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/13 14:55:08 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ten_pow(long n)
{
	int		i;
	size_t	pow;

	if (n == 0)
		return (1);
	if (n < 0)
		n = n * (-1);
	pow = 1;
	i = 0;
	while (n / pow != 0)
	{
		pow = pow * 10;
		i++;
	}
	return (i);
}

static int	negate_it(char *str, long n)
{
	str[0] = '-';
	if (n == LONG_MIN)
	{
		str[1] = '9';
		n = 223372036854775808;
	}
	else
		n *= -1;
	return (n);
}

static int	is_neg(long n)
{
	return (n < 0);
}

char	*ft_ltoa(long n)
{
	char	*str;
	int		neg;
	int		pow;

	neg = 0;
	if (n == -2147483648)
		neg++;
	pow = ten_pow(n);
	str = (char *)malloc(sizeof (char) * (pow + is_neg(n) + 1));
	if (str == 0)
		return (str);
	if (is_neg(n))
	{
		pow++;
		neg++;
		n = negate_it(str, n);
	}
	str[pow] = '\0';
	while (pow > neg)
	{
		pow--;
		str[pow] = '0' + n % 10;
		n /= 10;
	}
	return (str);
}
