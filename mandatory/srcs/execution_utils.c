/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:31:55 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/14 09:40:05 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	count_cmds(t_command *cmd)
{
	int	n;

	n = 1;
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		if (cmd->purpose == DELIM)
			n++;
		cmd = cmd->next;
	}
	return (n);
}
