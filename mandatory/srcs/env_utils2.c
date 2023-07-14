/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:05:16 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/14 20:54:52 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"
#include "stdarg.h"

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

	va_start(list, env);
	key = va_arg(list, char *);
	if (key && env_contain(key, env))
	{
		ptr = env_getptr(key, env);
		free_char_etoile_etoile(ptr->value);
		ptr->value = ft_split(char_arr, ':');
		return (1);
	}
	return (0);
}
