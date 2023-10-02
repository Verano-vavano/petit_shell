/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_assign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 22:43:32 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/02 22:43:41 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	assign_vars(t_command *cmd, t_env **env)
{
	bool		one;
	t_command	*cpy;

	one = true;
	cpy = cmd;
	while (cpy && cpy->purpose != CMD_DELIM)
	{
		if (cpy->purpose == DELIM)
			one = false;
		cpy = cpy->next;
	}
	if (!one)
		return ;
	while (cmd && cmd->purpose == VAR_ASSIGN)
	{
		if (!env || !(*env))
			*env = env_new(cmd->content, false);
		else
			env_update(cmd->content, false, env);
		cmd = cmd->next;
	}
}
