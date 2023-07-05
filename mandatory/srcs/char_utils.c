/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cute_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:49:50 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/05 12:34:59 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	is_strict_meta(char c)
{
	return (c == '|' || c == '&' || c == ';');
}

int	is_metachar(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '<' || c == '>');
}

int	is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_delim(char c)
{
	return (c == '\'' || c == '"' || c == '`' || c == '(' || c == ')'
		|| c == '{' || c == '}');
}

int	is_ender(char c, char new_c)
{
	return ((c == '(' && new_c == ')') || (c == '{' && new_c == '}')
		|| (c != '(' && c != '{' && c == new_c));
}
