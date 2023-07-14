/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_char_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:32:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/13 18:57:18 by hdupire          ###   ########.fr       */
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

char	is_quoted(char *s, int i, char quoted)
{
	printf("QUOTED = %c, s = %s\n", quoted, s + i);
	if ((s[i] == '\'' || s[i] == '"') && (i == 0 || s[i - 1] != '\\')
		&& (s[i] == quoted || !quoted))
		return (!quoted * s[i]);
	return (quoted);
}
