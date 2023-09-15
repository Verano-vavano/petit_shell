/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:46:48 by hdupire           #+#    #+#             */
/*   Updated: 2023/03/30 11:30:40 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	l;

	l = 0;
	while (s[l])
		l++;
	while (l != 0)
	{
		if (s[l] == (char)c)
			return ((char *)(s + l));
		l--;
	}
	if (s[0] == (char)c)
		return ((char *)(s));
	else
		return (0);
}
