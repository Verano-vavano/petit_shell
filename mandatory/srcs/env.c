/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:07:11 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/10 08:09:10 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"

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
