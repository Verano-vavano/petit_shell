/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_ex_portes_de_lutil.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:20:05 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/25 11:13:28 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

t_env	*dup_env(t_env *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(env->key);
	if (env->value != NULL)
		new->value = ft_strdup(env->value);
	else
		new->value = NULL;
	new->next = NULL;
	new->is_exported = env->is_exported;
	return (new);
}

static void	swap_content(t_env *curr, t_env *next)
{
	char	*yo_key;
	char	*yo_value;
	bool	yo_is_exp;

	yo_key = curr->key;
	yo_value = curr->value;
	yo_is_exp = curr->is_exported;
	curr->key = next->key;
	curr->value = next->value;
	curr->is_exported = next->is_exported;
	next->key = yo_key;
	next->value = yo_value;
	next->is_exported = yo_is_exp;
}

void	sort_env(t_env *head)
{
	int		swapped;
	t_env	*ptr;

	swapped = 1;
	while (swapped == 1)
	{
		swapped = 0;
		ptr = head;
		while (ptr && ptr->next)
		{
			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
			{
				swap_content(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
	}
}
