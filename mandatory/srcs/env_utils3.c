/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:40:28 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/14 21:37:32 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	env_size(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		if (env->is_exported)
			n++;
		env = env->next;
	}
	return (n);
}

static char	*get_env_val(t_env *env)
{
	char	*val;
	char	*return_val;
	char	*temp;

	val = env->value;
	return_val = ft_strjoin(env->key, "=");
	if (!return_val)
		return (0);
	temp = ft_strjoin(return_val, val);
	free(return_val);
	if (!temp)
		return (0);
	return_val = temp;
	return (return_val);
}

char	**re_char_etoile_etoilise_env(t_env *env)
{
	char	**c_env;
	int		len;
	int		i;

	if (!env)
		return (0);
	len = env_size(env);
	c_env = ft_calloc(len + 1, sizeof (char *));
	if (c_env == 0)
		return (0);
	i = 0;
	while (env)
	{
		if (env->is_exported)
		{
			c_env[i] = get_env_val(env);
			if (c_env[i] == 0)
			{
				free_char_etoile_etoile(c_env);
				return (0);
			}
			i++;
		}
		env = env->next;
	}
	return (c_env);
}

t_env *env_new_specific(char *key, char *value, bool is_exported)
{
	t_env *new;

	if (!key)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->is_exported = is_exported;
	new->next = NULL;
	return (new);
}
