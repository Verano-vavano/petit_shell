/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:07:11 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/05 16:13:01 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

t_env	*env_new(char *env_var, bool is_exported)
{
	t_env	*new;
	char	**tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	tmp = ft_split(env_var, '=');
	new->key = ft_strdup(tmp[0]);
	if (new->key[ft_strlen(new->key) - 1] == '+')
		new->key[ft_strlen(new->key) - 1] = 0;
	if (tmp[1])
		new->value = ft_split(tmp[1], ':');
	else if (!ft_strchr(env_var, '='))
		new->value = NULL;
	else
		new->value = ft_calloc(1, sizeof (char));
	new->next = NULL;
	new->is_exported = is_exported;
	free_char_etoile_etoile(tmp);
	return (new);
}

t_env	*env_init(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
		env_add(env_new(envp[i++], true), &env);
	if (!env_contain("PATH", env))
		env_add(env_new(STD_PATH, true), &env);
	return (env);
}
