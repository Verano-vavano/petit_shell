/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:40:28 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/10 12:49:32 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	env_create_add(char *key, char *value, t_env *env)
{
	t_env *created;

	created = malloc(sizeof(t_env *));
	if (!created)
		return (env_add(created, &env));
	created->key = key;
	created->value = malloc(sizeof(char *) * 2);
	created->value[0] = value;
	created->value[1] = NULL;
	created->next = NULL;
	env_add(created, &env);
}

static int	env_size(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		if (1) // !env->is_local
			n++;
		env = env->next;
	}
	return (n);
}

static char	*get_env_val(t_env *env)
{
	char	**val;
	char	*return_val;
	char	*temp;

	val = env->value;
	return_val = ft_strjoin(env->key, "=");
	while (val)
	{
		if (!return_val)
			return (0);
		temp = ft_strjoin(return_val, *val);
		free(return_val);
		if (!temp)
			return (0);
		return_val = temp;
		if (!val[1])
			break ;
		temp = ft_strjoin(return_val, ":");
		free(return_val);
		return_val = temp;
		val++;
	}
	return (return_val);
}

char	**re_char_etoile_etoilise_env(t_env *env)
{
	char	**c_env;
	int		len;
	int		i;

	len = env_size(env);
	c_env = ft_calloc(len + 1, sizeof (char *));
	if (c_env == 0)
		return (0);
	i = 0;
	while (env)
	{
		if (1) // !env->is_local
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
