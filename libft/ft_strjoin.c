/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:06:27 by hdupire           #+#    #+#             */
/*   Updated: 2023/03/28 17:12:41 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	size_t	i;
	char	*concat;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	concat = (char *)malloc(sizeof (char) * (l1 + l2 + 1));
	if (concat == 0)
		return (concat);
	i = 0;
	while (i < l1)
	{
		concat[i] = s1[i];
		i++;
	}
	while (i - l1 < l2)
	{
		concat[i] = s2[i - l1];
		i++;
	}
	concat[i] = '\0';
	return (concat);
}
