/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:05:16 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/05 13:01:54 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	redir_parser(char *s, char quoted)
{
	int	i;

	if (quoted)
		return (0);
	i = 0;
	while (s[i] && is_num(s[i]))
		i++;
	if (s[i] != '<' && s[i] != '>')
		return (0);
	while (s[i] && (s[i] == '<' || s[i] == '>'))
		i++;
	return (i);
}

int	handle_parenthesis(char *c, char c2, int dos)
{
	if (c2 == '(' && *c == ')')
		dos++;
	return (dos);
}

int	better_strlen(char *s)
{
	int		i;
	int		j;
	int		in_par;
	char	quoted;

	quoted = 0;
	in_par = 0;
	i = 0;
	while (s[i])
	{
		if (!quoted && is_strict_meta(s[i]))
			return (i);
		j = redir_parser(s + i, quoted);
		if (j && !i)
			return (i + j);
		else if (j)
			return (i);
		quoted = is_quoted(s, i, quoted);
		if (s[i] == '(' && !quoted)
			in_par++;
		else if (s[i] == ')' && !quoted)
			in_par--;
		if (is_separator(s[i]) && !quoted && !in_par)
			return (i);
		i++;
	}
	return (i);
}

int	ft_strlen_arg(char *s, int meta)
{
	int		i;
	char	c;

	if (!s[0] || s[0] == '#')
		return (0);
	i = 0;
	c = 's';
	if (meta)
	{
		c = s[i];
		while (s[i] == c || (s[i] == '>' && (i == 0 || s[i - 1] == '<')))
			i++;
		return (i);
	}
	return (better_strlen(s));
}
