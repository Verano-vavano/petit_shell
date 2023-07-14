/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:08:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/14 11:53:05 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

long	execute_the_line(t_command *cmd, t_env *env)
{
	//int				last_pid;
	int				n_cmd;
	t_process_cmd	cmd_processing;

	n_cmd = count_cmds(cmd);
	(void) env;
	while (n_cmd)
	{
		cmd_processing.redir = 0;
		if (get_cmd(&cmd_processing, cmd))
			return (1);
		/*if (cmd_args == 0)
			return ;
		last_pid = create_child(cmd_processing, env);
		clean_processing(cmd_processing);
		cmd = go_to_next_cmd(cmd);*/
		n_cmd--;
	}
	return (0);
}
