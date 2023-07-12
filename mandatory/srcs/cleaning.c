/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:25:59 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/12 17:46:51 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"

void	free_env(t_env *env)
{
	int	i;

	if (env)
	{
		free(env->key);
		if (env->value != NULL)
		{
			i = -1;
			while (env->value[++i])
				free(env->value[i]);
			free(env->value);
		}
	}
	free(env);
}

void	free_whole_env(t_env *env)
{
	t_env	*next;

	while (env != NULL)
	{
		next = env->next;
		free_env(env);
		free(env);
		env = next;
	}
}

void	free_command(t_command *l)
{
	t_command	*next;

	while (l && l->next)
	{
		next = l->next;
		free(l->content);
		free(l);
		l = l->next;
	}
	if (l && l->content)
		free(l->content);
	if (l)
		free(l);
}
