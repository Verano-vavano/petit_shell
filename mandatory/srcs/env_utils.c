/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:47:25 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/08 15:35:42 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

t_env	*env_last(t_env *env)
{
	if (!env)
		return (env);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	add_env(t_env **env, t_env *newest)
{
	t_env	*tmp;

	if (env && *env)
	{
		tmp = env_last(*env);
		tmp->next = newest;
	}
	else
		*env = newest;
}
