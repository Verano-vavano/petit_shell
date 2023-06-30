/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:05:16 by hdupire           #+#    #+#             */
/*   Updated: 2023/06/30 17:10:04 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	strlen_loop(char *s, int *i, char c)
{
	while (s[*i] && !is_separator(s[*i]))
	{
		if (is_metachar(s[*i]) && !is_delim(c))
			return (0);
		if (is_delim(s[*i]) && s[*i - 1] != '\\')
		{
			if (c == s[*i])
				c = ' ';
			else if (!(is_delim(c)))
				c = s[*i];
		}
		(*i)++;
	}
	return (c);
}

int	ft_strlen_arg(char *s, int meta)
{
	int		i;
	char	c;

	if (!s[0])
		return (0);
	c = s[0];
	i = 0;
	if (meta)
	{
		while (s[i] == c)
			i++;
		return (i);
	}
	while (1)
	{
		c = strlen_loop(s, &i, c);
		if (!s[i] || !is_delim(c) || c == 0)
			break ;
		while (s[i] && is_separator(s[i]))
			i++;
	}
	return (i);
}
