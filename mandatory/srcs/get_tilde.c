/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tilde.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:09:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/12 12:24:36 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	get_home(char **home, t_env *env)
{
	if (!env)
		return (0);
	while (env->next)
	{
		if (!ft_strcmp(env->key, "HOME"))
		{
			*home = *(env->value);
			return (1);
		}
		env = env->next;
	}
	if (!env || ft_strcmp(env->key, "HOME"))
		return (0);
	*home = *(env->value);
	return (1);
}
