/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:47:25 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/16 14:00:28 by hdupire          ###   ########.fr       */
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
	int		len;
	bool	changed;

	ptr = env;
	changed = false;
	len = ft_strlen(newest);
	changed = (newest[len - 1] == '+');
	if (changed)
		newest[len - 1] = 0;
	while (ptr)
	{
		if (ft_strcmp(newest, ptr->key) == 0)
		{
			if (changed)
				newest[len - 1] = '+';
			return (1);
		}
		else
			ptr = ptr->next;
	}
	if (changed)
		newest[len - 1] = '+';
	return (0);
}

void	env_add(t_env *newest, t_env **env)
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

// TODO print message d'erreur
void	env_del(char *del, t_env **env)
{
	t_env	*ptr;
	t_env	*prev;

	if (!env || !(*env))
		return ;
	ptr = *env;
	prev = NULL;
	while (ptr)
	{
		if (ft_strcmp(ptr->key, del) == 0)
		{
			if (prev == NULL && (*env)->next == NULL)
				*env = NULL;
			else if (prev == NULL)
				*env = (*env)->next;
			else
				prev->next = ptr->next;
			free_env(ptr);
			return ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}

char	*env_getval(char *key, t_env *env)
{
	t_env	*ptr;

	if (!env)
		return (0);
	ptr = env_getptr(key, env);
	if (!ptr || !ptr->value)
		return (NULL);
	return (ptr->value);
}
