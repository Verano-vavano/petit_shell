/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:05:16 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/24 16:55:10 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"
#include "stdarg.h"
#include <stdio.h>
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
		key[len - 1] = '\0';
	ptr = env_getptr(key, env);
	if (!ptr)
		return ;
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

void	env_update(char *str, bool is_exported, t_env **env)
{
	char	**tmp;
	t_env	*ptr;
	bool	add;
	char	*new;

	tmp = one_split(str, '=');
	add = (tmp[0][ft_strlen(tmp[0]) - 1] == '+');
	if (add)
		tmp[0][ft_strlen(tmp[0]) - 1] = 0;
	ptr = env_getptr(tmp[0], *env);
	if (!ptr)
		env_add(env_new_specific(tmp[0], tmp[1], is_exported), env);
	if (tmp[1] && ptr)
	{
		if (add && ptr->value)
			new = ft_strjoin(ptr->value, tmp[1]);
		else
			new = ft_strdup(tmp[1]);
		if (ptr->value)
			free(ptr->value);
		ptr->value = new;
	}
	if (ptr && !ptr->is_exported)
		ptr->is_exported = is_exported;
	free_char_etoile_etoile(tmp);
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
