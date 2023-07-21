/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 11:38:41 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/21 06:27:20 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	*init_it(const char *s, int start, int len, const char *to_mod)
{
	int		new_len;
	char	*new_s;

	if (ft_strlen(s) < (size_t)len + start)
		return (0);
	new_len = ft_strlen(s) - len + ft_strlen(to_mod) + 1;
	new_s = ft_calloc(new_len, sizeof (char));
	if (!new_s)
		return (0);
	return (new_s);
}

char	*ft_strreplace(const char *s, int start, int len, const char *to_mod)
{
	int		i;
	int		j;
	char	*new_s;

	new_s = init_it(s, start, len, to_mod);
	if (!new_s)
		return (0);
	j = -1;
	while (++j < start)
		new_s[j] = s[j];
	i = -1;
	while (to_mod[++i])
	{
		new_s[j] = to_mod[i];
		j++;
	}
	i = start + len - 1;
	while (s[++i])
	{
		new_s[j] = s[i];
		j++;
	}
	return (new_s);
}
