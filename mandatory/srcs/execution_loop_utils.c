/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_loop_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:03:04 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/12 16:03:17 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	init_cp(t_process_cmd *cmd_processing, t_tool *tool, t_command *cmd)
{
	cmd_processing->is_builtin = false;
	cmd_processing->is_parenthesis = (cmd && cmd->content
			&& cmd->content[0] == '(' && ft_strchr(cmd->content, ')'));
	cmd_processing->cmd_name = 0;
	cmd_processing->sub_cmd = !(tool->hist);
}

bool	has_command(t_command *cmd)
{
	while (cmd)
	{
		if (cmd && cmd->content && cmd->content[0] && cmd->purpose == COMMAND)
			return (true);
		cmd = cmd->next;
	}
	return (false);
}
