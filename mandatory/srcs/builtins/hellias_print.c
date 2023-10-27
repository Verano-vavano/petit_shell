/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hellias_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:57:50 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/27 17:51:03 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	print_alias_key(t_alias *alias)
{
	printfd(STDOUT_FILENO, "alias %s='%s'\n", alias->cmd, alias->replacer);
}

void	print_whole_alias(t_tool *tool)
{
	t_alias	*alias;

	sort_alias(tool);
	alias = tool->alias_start;
	while (alias)
	{
		print_alias_key(alias);
		alias = alias->next;
	}
}

bool	print_alias(char *arg, t_tool *tool)
{
	t_alias	*alias;

	alias = tool->alias_start;
	while (alias)
	{
		if (!ft_strcmp(alias->cmd, arg))
		{
			print_alias_key(alias);
			return (true);
		}
		alias = alias->next;
	}
	return (false);
}
