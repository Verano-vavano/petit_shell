/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:07:11 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/07 14:08:21 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"

t_env	*env_last(t_env *env)
{
	if (!env)
		return (env);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (env && *env)
	{
		tmp = env_last(*env);
		tmp->next = new;
	}
	else
		*env = new;
}

t_env	*env_new(char *env_var)
{
	t_env	*new;
	char	**tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	tmp = ft_split(env_var, '=');
	new->key = ft_strdup(tmp[0]);
	new->value = NULL;
	new->next = NULL;
	if (tmp[1])
	{
		printf("%s=%s\n",new->key,tmp[1]);
		if (ft_strcmp(new->key, "PATH"))
			new->value = ft_split(tmp[1], ':');
		else
		{
			new->value = malloc(sizeof(char *) * 2);
			new->value[0] = ft_strdup(tmp[1]);
			new->value[1] = NULL;
		}
	}
	else
		new->value = NULL;
	free_char_etoile_etoile(tmp);
	return (new);
}

t_env	*env_processing(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
		add_env(&env, env_new(envp[i++]));
	return (env);
}
