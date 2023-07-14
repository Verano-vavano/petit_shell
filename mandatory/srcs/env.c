/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:07:11 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/14 21:01:04 by tcharanc         ###   ########.fr       */
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
	if (tmp[1])
			new->value = ft_split(tmp[1], ':');
	else
		new->value = NULL;
	new->next = NULL;
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
		env_add(env_new(envp[i++]), &env);
	return (env);
}
