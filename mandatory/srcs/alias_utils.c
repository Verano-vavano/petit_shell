/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:19:20 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/02 15:32:17 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

t_command	*al_add_new_command(char *s, int l, t_command *n, t_command **st)
{
	if (*s && l)
	{
		n->next = ft_calloc(1, sizeof (t_command));
		if (!n->next)
		{
			free_command(*st);
			*st = 0;
			return (0);
		}
		n = n->next;
	}
	return (n);
}

t_alias	*get_alias(char *content, t_alias *alias)
{
	while (alias)
	{
		if (!ft_strcmp(content, alias->cmd))
			return (alias);
		alias = alias->next;
	}
	return (0);
}
