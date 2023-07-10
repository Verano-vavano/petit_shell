/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:13:48 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/10 08:21:36 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	check_metachar(char *line)
{
	int	i;
	int	meta;

	i = 0;
	meta = 0;
	while (line[i])
	{
		if (is_metachar(line[i]) && meta == 2)
			return (syntax_error(line + i, 1));
		else if (!meta && is_metachar(line[i]))
			meta = 1;
		else if (meta && (is_metachar(line[i]) || is_separator(line[i])))
			meta = 2;
		else if (meta && !is_separator(line[i]))
			return (0);
		i++;
	}
	return (0);
}

static int	check_parenthesis(char *line, int first, int dollar)
{
	int	i;
	int	j;

	i = 1;
	while (is_separator(line[i]))
		i++;
	if ((first || dollar) && line[i] != ')' && line[i] != '\0')
		return (0);
	else if (line[i] == ')')
		return (syntax_error(line + i, 1));
	else if (!(first || dollar) && line[i] != ')' && line[i] != '\0')
	{
		j = 1;
		while (line[i + j - 1]
			&& line[i + j - 1] != ')' && !is_separator(line[i + j - 1]))
			j++;
		return (syntax_error(line + i, j - 1));
	}
	return (0);
}

int	check_syntax(char *line)
{
	int	first;
	int	i;
	int	dollar;

	first = 1;
	i = 0;
	while (line[i])
	{
		if (first && is_strict_meta(line[i]))
			return (syntax_error(line + i, -1));
		if (is_metachar(line[i]) && check_metachar(line + i))
			return (1);
		if (line[i] == '(' && check_parenthesis(line + i, first, dollar))
			return (1);
		first = is_cmd_delim(line + i);
		dollar = (line[i] == '$' || (dollar && line[i] == '('));
		printf("%c %d\n", line[i], first);
		i += (first && line[i] != ';');
		i++;
	}
	return (0);
}
