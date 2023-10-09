/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 19:12:14 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/09 17:50:03 by hdupire          ###   ########.fr       */
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

void	init_ps(t_env **env, t_set *settings)
{
	if (!env_contain("PS1", *env))
	{
		if (settings->ps == 2)
			env_add(env_new(STD_PS1, false), env);
		else if (settings->ps == 1)
			env_add(env_new(STD_LOW_PS1, false), env);
	}
	if (!env_contain("PS2", *env))
	{
		if (settings->ps == 2)
			env_add(env_new(STD_PS2, false), env);
		else if (settings->ps == 1)
			env_add(env_new(STD_LOW_PS2, false), env);
	}
}
