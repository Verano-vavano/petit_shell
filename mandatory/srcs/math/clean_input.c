/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:24:02 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/20 15:00:28 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "math.h"
#include <unistd.h>

static bool is_ignore_char(char c)
{
	return (c == '$' || c == '"' || is_newline(c));
}

static size_t len_no_junk(const char *cmd)
{
	size_t len;

	len = 0;
	while(is_spc(*cmd))
		cmd++;
	while(*cmd)
	{
		if (*cmd == '$' && *(cmd + 1) == '(' && *(cmd + 2) == '(')
		{
			cmd += 3;
			while(is_spc(*cmd))
				cmd++;
		}
		else if (*cmd == ')' && *(cmd + 1) == ')')
			cmd += 2;
		else if (!is_ignore_char(*cmd++))
			len++;
	}
	return (len);
}

//  remove from input string
//  - leading whitespaces
//  - $((
//  - ))
//  - $
//  - "
char *clean_input(const char *cmd)
{
	char *without_delimiters;
	int	i;

	without_delimiters = malloc(sizeof(char) * (len_no_junk(cmd) + 1));
	if (!without_delimiters)
		return (NULL);
	i = 0;
	while(*cmd)
	{
		if (*cmd == '$' && *(cmd + 1) == '(' && *(cmd + 2) == '(')
		{
			cmd += 3;
			while(is_spc(*cmd))
				cmd++;
		}
		else if (*cmd == ')' && *(cmd + 1) == ')')
			cmd += 2;
		else if (!is_ignore_char(*cmd))
			without_delimiters[i++] = *cmd++;
	}
	without_delimiters[i] = '\0';
	return (without_delimiters);
}
