/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:50:14 by hdupire           #+#    #+#             */
/*   Updated: 2023/03/29 16:16:15 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ten_pow(int n)
{
	int		i;
	size_t	pow;

	if (n == 0)
		return (1);
	else if (n == -2147483648)
		return (10);
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

static int	negate_it(char *str, int n)
{
	str[0] = '-';
	if (n == -2147483648)
	{
		str[1] = '2';
		n = 147483648;
	}
	else
		n *= -1;
	return (n);
}

static int	is_neg(int n)
{
	return (n < 0);
}

char	*ft_itoa(int n)
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
