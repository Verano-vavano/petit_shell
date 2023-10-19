/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iiitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:23:48 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/19 16:59:16 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

char	*zero_str(void)
{
	char	*zero;

	zero = malloc(2 * sizeof(char));
	if (!zero)
		return (NULL);
	zero[0] = '0';
	zero[1] = '\0';
	return (zero);
}

int	get_len(long long n)
{
	int	len;

	len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	rev_str(char *str, int len)
{
	int		start;
	int		end;
	char	tmp;

	start = 0;
	end = len - 1;
	while (start < end)
	{
		tmp = str[start];
		str[start] = str[end];
		str[end] = tmp;
		start++;
		end--;
	}
}

int	fill_str(char *str, long long n, int neg)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		str[len] = (char)((n % 10) + '0');
		n /= 10;
		len++;
	}
	if (neg)
	{
		str[len] = '-';
		len++;
	}
	str[len] = '\0';
	return (len);
}

char	*ft_iiitoa(long long n)
{
	int		len;
	int		neg;
	char	*result;

	if (n == 0)
		return (zero_str());
	neg = n < 0;
	if (neg)
		n = -n;
	len = get_len(n);
	result = malloc((len + neg + 1) * sizeof(char));
	if (!result)
		return (NULL);
	len = fill_str(result, n, neg);
	rev_str(result, len);
	return (result);
}
