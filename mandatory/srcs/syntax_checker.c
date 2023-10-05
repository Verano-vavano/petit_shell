/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:13:48 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/04 20:02:20 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	check_loop(char *line, int f, int i, int d)
{
	char	q;

	q = 0;
	while (line[i])
	{
		if (line[i] == '#')
			return (0);
		q = is_quoted(line, i, q);
		if (f && is_strict_meta(line[i]))
			return (syntax_error(line + i, -1));
		else if (!q && ((is_metachar(line[i]) && check_metachar(line + i))
				|| (line[i] == '(' && check_parenthesis(line, f, d, i))
				|| (line[i] == '{' && f && check_cbrackets(line + i))
				|| ((line[i] == '<' || line[i] == '>') && redir_ok(line + i))))
			return (2);
		f = ((is_cmd_delim(line + i) || (f && is_separator(line[i]))) && !q);
		d = (line[i] == '$' || (d && line[i] == '('));
		i += ((line[i] == '|' && line[i + 1] == '|')
				|| (line[i] == '&' && line[i + 1] == '&')) + 1;
		while (is_separator(line[i]))
			i++;
	}
	return (0);
}

int	check_syntax(char *line)
{
	int		first;
	int		i;
	int		dollar;

	first = 1;
	i = 0;
	dollar = 0;
	return (check_loop(line, first, i, dollar));
}
