/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:25:59 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/24 16:54:04 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"

void	free_env(t_env *env)
{
	if (env)
	{
		free(env->key);
		if (env->value != NULL)
			free(env->value);
	}
	free(env);
}

void	free_whole_env(t_env *env)
{
	t_env	*ptr;
	t_env	*next;

	ptr = env;
	while (ptr)
	{
		next = ptr->next;
		free_env(ptr);
		ptr = next;
	}
	env = NULL;
}

int	free_command(t_command *l)
{
	t_command	*next;

	while (l && l->next)
	{
		next = l->next;
		free(l->content);
		free(l);
		l = next;
	}
	if (l && l->content)
		free(l->content);
	if (l)
		free(l);
	return (-1);
}
