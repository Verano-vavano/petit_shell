/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 02:07:30 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/02 23:20:14 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	check_chars(char *s, char *long_lim, size_t len_s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] > long_lim[i])
			break ;
		else if (s[i] < long_lim[i])
			i = len_s;
		i++;
	}
	free(long_lim);
	return (s[i] == 0);
}

bool	is_long(char *s, bool alnum)
{
	int		size_max;
	size_t	len_s;
	char	*long_lim;

	if (!s || (alnum && !is_valid_num(s)))
		return (false);
	if (s[0] == '-')
		size_max = ft_longlen(LONG_MIN) + 1;
	else
		size_max = ft_longlen(LONG_MAX);
	len_s = ft_strlen(s);
	if (len_s != (size_t) size_max)
		return (len_s < (size_t) size_max);
	if (s[0] == '-')
		long_lim = ft_ltoa(LONG_MIN);
	else
		long_lim = ft_ltoa(LONG_MAX);
	if (!long_lim)
		return (false);
	return (check_chars(s, long_lim, len_s));
}
