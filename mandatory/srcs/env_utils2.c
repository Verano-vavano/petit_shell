/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:05:16 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/14 21:18:43 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"
#include "stdarg.h"
#include <string.h>

t_env	*env_getptr(char *key, t_env *env)
{
	t_env *ret;

	ret = env;
	while(ret)
		if (ft_strcmp(ret->key, key) == 0)
			return (ret);
		else
			ret = ret->next;
	return (ret);
}

int	env_update(char *char_arr, t_env *env, ...)
{
	va_list	list;
	char	*key;
	t_env	*ptr;
	char	**new_value;

	va_start(list, env);
	key = va_arg(list, char *);
	if (key && env_contain(key, env))
	{
		ptr = env_getptr(key, env);
		free_char_etoile_etoile(ptr->value);
		ptr->value = ft_split(char_arr, ':');
		return (1);
	}
	else
	{
		ptr = env_new(char_arr);
		printf("update via export = %s\n",ptr->key);
		if (env_contain(ptr->key, env))
		{
			key = ft_strdup(ptr->key);
			new_value = dup_char_array(ptr->value);
			free_env(ptr);
			ptr = env_getptr(key, env);
			free_char_etoile_etoile(ptr->value);
			ptr->value = new_value;
			free(key);
			printf("wow ca existe\n");
		}
		else
		{
			printf("hmm connait pas..\n");
			env_add(ptr, &env);
		}
	}
	return (0);
}
