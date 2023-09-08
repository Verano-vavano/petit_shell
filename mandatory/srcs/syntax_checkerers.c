/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checkerers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 23:55:27 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/08 17:09:10 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	check_metachar(char *line)
{
	int	i;

	i = 0;
	if ((line[0] == '<' || line[0] == '>') && line[1] == '&')
		return (0);
	else if (line[0] == '<' && line[1] == '<' && line[2] == '<')
		return (0);
	else if (is_strict_meta(line[i]) && is_strict_meta(line[i + 1])
		&& line[i] != line[i + 1])
		return (syntax_error(line + i + 1, 1));
	return (0);
}

int	check_parenthesis(char *line, int first, int dollar)
{
	int	i;
	int	j;

	i = 1;
	while (is_separator(line[i]))
		i++;
	if ((first || dollar) && line[i] != ')' && line[i] != '\0')
		return (0);
	else if (!(first || dollar) && line[i] == '(')
		return (syntax_error(line + i, 1));
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

int	check_cbrackets(char *line)
{
	int	i;

	if (line[1] == '}')
		return (0);
	i = 1;
	while (line[i] && is_separator(line[i]))
		i++;
	if (line[i] == '}')
		return (syntax_error("}", 1));
	return (0);
}

int	redir_ok(char *line)
{
	int	i;

	if (line[0] == '>' && line[1] == '<')
		return (syntax_error("<", 1));
	else if (line[0] == '>' && line[1] == '<'
		&& line[2] && (line[2] == '<' || line[2] == '>'))
		return (syntax_error(line + 2, 1));
	else if (line[0] == line[1]
		&& (line[2] == '<' || line[2] == '>') && line[2] != line[0])
		return (syntax_error(line + 2, 1));
	i = 0;
	while (line[i] == '<' || line[i] == '>')
		i++;
	while (line[i] && is_separator(line[i]))
		i++;
	if (is_metachar(line[i]))
		return (syntax_error(line + i, -1));
	if (!line[i] || (line[i] == '&' && line[i + 1] == '\0'))
		return (syntax_error("newline", 7));
	return (0);
}
