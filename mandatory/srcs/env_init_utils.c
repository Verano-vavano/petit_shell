/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 19:12:14 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/16 13:55:41 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	increment_shlvl(t_env **env)
{
	t_env	*shlvl;
	bool	sign;
	int		lvl;
	char	*temp_lvl;

	shlvl = env_getptr("SHLVL", *env);
	if (!shlvl || !shlvl->value || !(shlvl->value[0]))
		env_add(env_new("SHLVL=1", true), env);
	else
	{
		sign = (shlvl->value[0] == '+' || shlvl->value[0] == '-');
		if (!is_all_num(shlvl->value + sign))
			return (env_add(env_new("SHLVL=1", true), env));
		lvl = ft_atoi(shlvl->value);
		lvl = (0 * (lvl < 0) + (lvl + 1) * (lvl >= 0));
		temp_lvl = ft_itoa(lvl);
		if (temp_lvl)
		{
			env_change_val("SHLVL", temp_lvl, *env, true);
			return (free(temp_lvl));
		}
		env_add(env_new("SHLVL=1", true), env);
	}
}
