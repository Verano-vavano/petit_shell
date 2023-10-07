/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quoted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:34:27 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/07 12:22:06 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

char	is_quoted(char *s, int i, char quoted)
{
	if (quoted == CQUOTES && (i == 0 || s[i - 1] != '\\') && s[i] == '\'')
		return (0);
	if (!quoted && (s[i] == '\'' || s[i] == '"')
		&& (i == 0 || s[i - 1] != '\\'))
		return (s[i]);
	else if (!quoted)
		return (0);
	if (s[i] == '\'' && (s[i] == quoted || !quoted))
		return (!quoted * s[i]);
	if (s[i] == '"' && (i == 0 || s[i - 1] != '\\')
		&& (s[i] == quoted || !quoted))
		return (!quoted * s[i]);
	return (quoted);
}

char	is_quoted_bk(char *s, int i, char quoted, bool bk)
{
	if (quoted == CQUOTES && !bk && s[i] == '\'')
		return (0);
	if (!quoted && (s[i] == '\'' || s[i] == '"') && !bk)
		return (s[i]);
	else if (!quoted)
		return (0);
	if (s[i] == '\'' && (s[i] == quoted || !quoted))
		return (!quoted * s[i]);
	if (s[i] == '"' && !bk
		&& (s[i] == quoted || !quoted))
		return (!quoted * s[i]);
	return (quoted);
}
