/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:22:35 by hdupire           #+#    #+#             */
/*   Updated: 2023/04/08 09:39:21 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	fill_space(int length, int zeroes)
{
	char	c;

	c = ' ';
	if (zeroes)
		c = '0';
	while (length > 0)
	{
		write(1, &c, 1);
		length--;
	}
}

void	spaces_before(size_t n, t_flags flags, t_total *t)
{
	if (flags.minus == 0)
	{
		fill_space(flags.spaces_count - n, flags.zeroes);
		if (flags.spaces_count > n)
			t->written += flags.spaces_count - n;
	}
}

void	spaces_after(size_t n, t_flags flags, t_total *t)
{
	if (flags.minus && n < flags.spaces_count)
	{
		fill_space(flags.spaces_count - n, 0);
		if (flags.spaces_count > n)
			t->written += flags.spaces_count - n;
	}
}

int	char_in_n_str(char c, const char *s, int n)
{
	int	i;

	i = 0;
	while (s[i] && i < n)
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

int	len_num(long i, int div_factor)
{
	int	n;

	n = 0;
	if (i == 0)
		return (1);
	while (i != 0)
	{
		n++;
		i /= div_factor;
	}
	return (n);
}
