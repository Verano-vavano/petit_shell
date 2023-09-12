/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:05:16 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/11 20:09:27 by tcharanc         ###   ########.fr       */
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

static void	env_change_val_rfunk(t_env *ptr, char *value, bool add)
{
	char	*temp;

	if (add && ptr->value)
		{
			temp = ft_strjoin(ptr->value, value);
			if (!temp)
				return ;
			free(ptr->value);
			ptr->value = ft_strdup(temp);
			free(temp);
		}
	else
	{
		if (ptr->value)
			free(ptr->value);
		ptr->value = ft_strdup(value);
	}
}

void	env_change_val(char *key, char *value, t_env *env, bool is_exp)
{
	t_env	*ptr;
	bool	add;
	int		len;

	len = ft_strlen(key);
	add = (key[len - 1] == '+');
	if (add)
		key[len - 1] = 0;
	ptr = env_getptr(key, env);
	if (value)
		env_change_val_rfunk(ptr, value, add);
	else if (!add)
	{
		free(ptr->value);
		ptr->value = ft_calloc(1, sizeof (char));
	}
	if (is_exp)
		ptr->is_exported = true;
}

void	env_update(char *char_arr, bool is_exported, t_env *env, ...)
{
	va_list	list;
	char	*key;
	char	**tmp;

	va_start(list, env);
	key = va_arg(list, char *);
	if (key && env_contain(key, env))
		env_change_val(key, char_arr, env, is_exported);
	else
	{
		if (!ft_strchr(char_arr, '='))
			return ;
		tmp = ft_split(char_arr, '=');
		if (env_contain(tmp[0], env))
			env_change_val(tmp[0], tmp[1], env, is_exported);
		else
			env_add(env_new(char_arr, is_exported), &env);
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
