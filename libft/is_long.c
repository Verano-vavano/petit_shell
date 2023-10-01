/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 02:07:30 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/01 14:28:44 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_long(char *s, bool alnum)
{
	int		size_max;
	size_t	len_s;
	int		i;
	char	*long_lim;

	if (alnum && !is_valid_num(s))
		return (false);
	size_max = ft_longlen(LONG_MIN);
	len_s = ft_strlen(s);
	if (len_s != (size_t) size_max)
		return (len_s < (size_t) size_max);
	if (s[0] == '-')
		long_lim = ft_ltoa(LONG_MIN);
	else
		long_lim = ft_ltoa(LONG_MAX);
	if (!long_lim)
		return (false);
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
