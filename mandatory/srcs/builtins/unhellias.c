/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unhellias.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:02:58 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/29 20:16:32 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static bool	remove_alias(char *key, t_tool *t)
{
	t_alias	*prev;
	t_alias	*alias;

	prev = 0;
	alias = t->alias_start;
	while (alias)
	{
		if (ft_strcmp(key, alias->cmd) == 0)
		{
			if (prev)
				prev->next = alias->next;
			else
				t->alias_start = alias->next;
			if (!alias->next)
				t->alias_end = 0;
			free(alias->cmd);
			free(alias->replacer);
			free(alias);
			return (0);
		}
		prev = alias;
		alias = alias->next;
	}
	printfd(ERR, "unalias: %s: not found\n", key);
	return (1);
}

int	unhellias(char **cmd, t_tool *t)
{
	int	ret;

	ret = 0;
	cmd++;
	if (!(*cmd))
	{
		printfd(ERR, "unalias: usage: unalias name [name ...]]\n");
		return (2);
	}
	while (*cmd)
	{
		if (remove_alias(*cmd, t) && !ret)
			ret = 1;
		cmd++;
	}
	return (ret);
}
