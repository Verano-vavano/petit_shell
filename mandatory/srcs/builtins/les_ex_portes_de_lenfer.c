/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_ex_portes_de_lenfer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:45:59 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/10 10:02:22 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"

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

	i = 0;
	while (s[i])
	{
		write(1, s + i, 1);
		i++;
	}
	write(1, "\n", 1);
}

t_env	*dup_env(t_env *env)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(env->key);
	if (env->value)
	{
	}
	else
		new->value = NULL;
	return (new);
}

// void	swap(t_env **ptr, t_env **ptr_next)
// {
// }

// void sort_env(t_env *env)
// {
// 	int		swapped;
// 	t_env	*ptr;
//
// 	swapped = 1;
// 	while(swapped)
// 	{
// 		ptr = env;
// 		swapped = 0;
// 		while(ptr)
// 		{
// 			if (!ptr->next)
// 				break ;
// 			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
// 			{
// 				swap(&ptr, &ptr->next);
// 				swapped = 1;
// 			}
// 			ptr = ptr->next;
// 		}
// 	}
// }
//
void	les_ex_portes_de_lenfer(t_command *lexed, t_env *env)
{
	t_env	*sorted_env;
	t_env	*ptr;

	ptr = env;
	sorted_env = NULL;
	while (ptr->next)
	{
		add_env(&sorted_env, dup_env(ptr));
		ptr = ptr->next;
	}
	printf("before %s & %s\n", ptr->key, ptr->next->key);
	printf("after %s & %s\n", ptr->key, ptr->next->key);
	// sort_env(sorted_env);
	// env_infernal(sorted_env);
	(void)lexed;
	// free_whole_env(sorted_env);
}
