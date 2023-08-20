/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:05:16 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/19 20:18:36 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	redir_parser(char *s)
{
	int	i;

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

static char	strlen_loop(char *s, int *i, char c, int *dos)
{
	while (s[*i] && !is_separator(s[*i]))
	{
		if (is_metachar(s[*i]) && !is_delim(c))
			return (0);
		if (is_delim(s[*i]) && (*i == 0 || s[*i - 1] != '\\')
			&& (c == s[*i] || !is_delim(c)))
		{
			if (c == s[*i] && *dos == 0)
				c = ' ';
			else if (!(is_delim(c)) && s[*i] != ')')
				c = s[*i];
			else if (*dos == 1 && c == s[*i])
				(*dos)--;
			if (c == '(')
				c = ')';
		}
		*dos = handle_parenthesis(&c, s[*i], *dos);
		(*i)++;
	}
	return (c);
}

int	ft_strlen_arg(char *s, int meta)
{
	int		i;
	int		j;
	int		dos;
	char	c;

	if (!s[0] || s[0] == '#')
		return (0);
	i = 0;
	c = 's';
	if (meta && s[i] != '<' && s[i] != '>')
	{
		c = s[i];
		while (s[i] == c)
			i++;
		return (i);
	}
	dos = 0;
	while (c)
	{
		j = redir_parser(s);
		if (j)
			return (j);
		c = rescue_funk(s, 0, &i, strlen_loop(s, &i, c, &dos));
	}
	return (i);
}
