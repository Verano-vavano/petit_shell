/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_ex_portes_de_lenfer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:45:59 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/10 19:16:31 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"
#include <string.h>

char	**dup_paths(char **paths)
{
	int		i;
	char	**cpy;

	i = 0;
	while (paths[i])
		i++;
	cpy = malloc(sizeof(char *) * i + 1);
	i = -1;
	while (paths[++i])
		cpy[i] = ft_strdup(paths[i]);
	cpy[i] = NULL;
	return (cpy);
}

t_env	*dup_env(t_env *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(env->key);
	if (env->value != NULL)
	{
		if (ft_strcmp("PATH", env->key) == 0)
			new->value = dup_paths(env->value);
		else
		{
			new->value = malloc(sizeof(char *) * 2);
			new->value[0] = ft_strdup(env->value[0]);
			new->value[1] = NULL;
		}
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	swap_content(t_env *curr, t_env *next)
{
	char	*yo_key;
	char	**yo_value;

	yo_key = curr->key;
	yo_value = curr->value;
	curr->key = next->key;
	curr->value = next->value;
	next->key = yo_key;
	next->value = yo_value;
}

void	sort_env(t_env *head)
{
	int		swapped;
	t_env	*ptr;

	swapped = 1;
	while (swapped == 1)
	{
		swapped = 0;
		ptr = head;
		while (ptr->next)
		{
			if (strcmp(ptr->key, ptr->next->key) > 0)
			{
				swap_content(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
	}
}

// if exporting a var, check if already exist
void	les_ex_portes_de_lenfer(t_command *lexed, t_env *env)
{
	t_env	*ptr;
	t_env	*sorted_env;

	ptr = env;
	if (!lexed->next)
	{
		sorted_env = NULL;
		while (ptr->next)
		{
			add_env(&sorted_env, dup_env(ptr));
			ptr = ptr->next;
		}
		sort_env(sorted_env);
		env_infernal(sorted_env, "declare -x ", NULL);
		free_whole_env(sorted_env);
	}
	else
	{
		while (lexed->next)
		{
			add_env(&env, env_new(lexed->next->content));
			lexed = lexed->next;
		}
	}
}
