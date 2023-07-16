/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:05:16 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/16 02:26:51 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"
#include "stdarg.h"
#include <string.h>

t_env	*env_getptr(char *key, t_env *env)
{
	t_env	*ret;

	ret = env;
	while (ret)
		if (ft_strcmp(ret->key, key) == 0)
			return (ret);
	else
		ret = ret->next;
	return (ret);
}

void	env_change_val(char *key, char *value, t_env *env)
{
	t_env	*ptr;

	ptr = env_getptr(key, env);
	free_char_etoile_etoile(ptr->value);
	ptr->value = ft_split(value, ':');
}

void	env_update(char *char_arr, t_env *env, ...)
{
	va_list	list;
	char	*key;
	char	**tmp;

	va_start(list, env);
	key = va_arg(list, char *);
	if (key && env_contain(key, env))
		env_change_val(key, char_arr, env);
	else
	{
		tmp = ft_split(char_arr, '=');
		if (env_contain(tmp[0], env))
			env_change_val(tmp[0], tmp[1], env);
		else
			env_add(env_new(char_arr), &env);
		free_char_etoile_etoile(tmp);
	}
}

int	env_isdefined(char *key, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (1);
		env = env->next;
	}
	return (0);
}
