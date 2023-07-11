/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:47:25 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/11 13:49:48 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include <string.h>

t_env	*env_last(t_env *env)
{
	if (!env)
		return (env);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

int	check_existence(char *newest, t_env **env)
{
	t_env	*ptr;

	ptr = *env;
	while (ptr)
		if (strcmp(newest, ptr->key) == 0)
			return (1);
	else
		ptr = ptr->next;
	return (0);
}

void	add_env(t_env **env, t_env *newest)
{
	t_env	*tmp;

	if (check_existence(newest->key, env))
		return ;
	if (env && *env)
	{
		tmp = env_last(*env);
		tmp->next = newest;
	}
	else
		*env = newest;
}
