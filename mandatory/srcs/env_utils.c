/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:47:25 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/14 20:55:23 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

int	env_contain(char *newest, t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
		if (ft_strcmp(newest, ptr->key) == 0)
			return (1);
	else
		ptr = ptr->next;
	return (0);
}

void	env_add(t_env *newest, t_env **env)
{
	t_env	*tmp;

	if (env_contain(newest->key, *env))
		return ;
	if (env && *env)
	{
		tmp = env_last(*env);
		tmp->next = newest;
	}
	else
		*env = newest;
}

// TODO print message d'erreur
void	env_del(char *del, t_env **env)
{
	t_env	*ptr;
	t_env	*prev;

	ptr = *env;
	prev = NULL;
	while (ptr)
	{
		if (ft_strcmp(ptr->key, del) == 0)
		{
			if (prev == NULL)
				*env = (*env)->next;
			else
				prev->next = ptr->next;
			free_env(ptr);
		}
		prev = ptr;
		ptr = ptr->next;
	}
//	printf("Wesh le nom n'a pas ete trouve dans l'env\n");
}

char	**env_getval(char *key, t_env *env)
{
	if (!env)
		return (0);
	while (env->next)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	if (!ft_strcmp(env->key, key))
		return (env->value);
	return (0);
}
