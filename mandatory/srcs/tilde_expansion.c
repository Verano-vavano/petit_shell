/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:00:49 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/11 19:47:20 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	check_env_user(char **home, t_env *env)
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

void	tilde_expansion(t_command *cmd, t_env *env)
{
	//static char	*username;
	char		*to_sub;
	int			is_set;

	to_sub = 0;
	is_set = check_env_user(&to_sub, env);
	printf("%d %s\n", is_set, to_sub);
	(void) cmd;
	/*if (!is_set && !username)
		username = get_username();
	if (!is_set)
		get_path_from_username();*/
}
