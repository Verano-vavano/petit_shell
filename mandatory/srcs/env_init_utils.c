/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 19:12:14 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/12 10:02:19 by tcharanc         ###   ########.fr       */
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
		{
			env_add(env_new("SHLVL=1", true), env);
			return ;
		}
		lvl = ft_atoi(shlvl->value);
		if (lvl < 0)
			lvl = 0;
		else
			lvl++;
		temp_lvl = ft_itoa(lvl);
		if (temp_lvl)
		{
			env_change_val("SHLVL", temp_lvl, *env, true);
			free(temp_lvl);
			return ;
		}
		env_add(env_new("SHLVL=1", true), env);
	}
}
