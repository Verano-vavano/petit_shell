/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_ex_portes_de_lenfer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:45:59 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/10 17:32:18 by tcharanc         ###   ########.fr       */
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

void	ft_putstr(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		write(1, s + i, 1);
	write(1, "\n", 1);
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
		// if (ft_strcmp("PATH",env->key) == 0)
		// 	new->value =  dup_paths(env->value);
		// else
		// {
			new->value = malloc(sizeof(char *) * 2);
			new->value[0] = ft_strdup(env->value[0]);
			new->value[1] = NULL;
		// }
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}


void swap2(t_env *prev, t_env *curr)
{
	t_env *tmp;

	tmp = curr->next;
	curr->next = prev;
	prev->next = tmp;
}

void swap3(t_env *prev, t_env *curr, t_env *next)
{
	t_env *tmp;

	tmp = next->next;
	prev->next = next;
	next->next = curr;
	curr->next = tmp;
}

void neovimcestnul(t_env *head)
{
	while (head->next)
	{
		printf("%s\n", head->key);
		head = head->next;
	}
}

void swap_content(t_env *curr, t_env *next)
{
	char *yo_key;
	char **yo_value;

	yo_key = curr->key;
	yo_value = curr->value;
	curr->key = next->key;
	curr->value = next->value;
	next->key = yo_key;
	next->value = yo_value;
}

void	sort_env(t_env *head)
{
	int swapped;
	t_env *ptr;

	swapped = 1;
	while(swapped == 1)
	{
		swapped = 0;
		ptr = head;
		printf("WAW\n");
		while(ptr->next)
		{
			printf("%s || %s\n", ptr->key, ptr->next->key);
			if (strcmp(ptr->key, ptr->next->key) > 0)
			{
				swap_content(ptr, ptr->next);
				printf("SWOOPED\n");
				swapped = 1;
			}
			ptr = ptr->next;
		}
	}
}


void	les_ex_portes_de_lenfer(t_command *lexed, t_env *env)
{
	t_env	*ptr;
	t_env	*sorted_env;

	ptr = env;
	sorted_env = NULL;
	while (ptr->next)
	{
		add_env(&sorted_env, dup_env(ptr));
		ptr = ptr->next;
	}
	printf("%s / %s\n",sorted_env->key,sorted_env->next->key);
	sort_env(sorted_env);
	printf("%s / %s\n",sorted_env->key,sorted_env->next->key);
	// env_infernal(sorted_env);
	free_whole_env(ptr);
	(void)lexed;
}
