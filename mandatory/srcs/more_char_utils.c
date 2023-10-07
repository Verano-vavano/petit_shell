/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_char_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:32:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/07 12:22:24 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

char	convert_to_closing(char c)
{
	if (c == '(')
		return (')');
	else if (c == '{')
		return ('}');
	return (c);
}

int	is_cmd_delim(char *c)
{
	if (*c == ';')
		return (1);
	else if (*c == '&' && *(c + 1) == '&')
		return (1);
	else if (*c == '|' && *(c + 1) == '|')
		return (1);
	return (0);
}

int	is_num(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_all_num(char *s)
{
	while (*s)
	{
		if (!is_num(*s))
			return (0);
		s++;
	}
	return (1);
}
