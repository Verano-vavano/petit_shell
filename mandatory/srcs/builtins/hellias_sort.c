/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hellias_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:55:41 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/02 13:56:00 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	swap_alias(t_alias *p, t_alias *a, t_alias *n, t_tool *t)
{
	if (t->alias_start == a)
		t->alias_start = n;
	if (t->alias_end == n)
		t->alias_end = a;
	if (p)
		p->next = n;
	a->next = n->next;
	n->next = a;
}

static bool	sort_spin(t_tool *tool)
{
	bool	changed;
	int		diff;
	t_alias	*alias;
	t_alias	*prev;

	prev = 0;
	changed = false;
	alias = tool->alias_start;
	while (alias && alias->next)
	{
		diff = ft_strcmp(alias->cmd, alias->next->cmd);
		if (diff > 0)
		{
			swap_alias(prev, alias, alias->next, tool);
			changed = true;
		}
		prev = alias;
		alias = alias->next;
	}
	return (changed);
}

void	sort_alias(t_tool *tool)
{
	if (!tool->alias_start)
		return ;
	while (sort_spin(tool))
		continue ;
}
