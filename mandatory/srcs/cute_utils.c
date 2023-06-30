/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cute_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:49:50 by hdupire           #+#    #+#             */
/*   Updated: 2023/06/30 18:03:05 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

t_command	*init_command_arg(t_command *start)
{
	t_command	*new_arg;

	new_arg = ft_calloc(1, sizeof (t_command));
	if (new_arg == 0)
	{
		free_linked_list(start);
		return (0);
	}
	return (new_arg);
}

int	is_strict_meta(char c)
{
	return (c == '|' || c == '&' || c == ';');
}

int	is_metachar(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '(' || c == ')'
		|| c == '<' || c == '>');
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
