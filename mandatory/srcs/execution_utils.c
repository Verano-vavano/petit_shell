/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:31:55 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/16 19:25:05 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	count_cmds(t_command *cmd)
{
	int		n;

	n = 1;
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		if (cmd->purpose == DELIM)
			n++;
		cmd = cmd->next;
	}
	return (n);
}

void	free_redirs(t_redir_pipe *redir)
{
	t_redir_pipe	*next;

	while (redir)
	{
		next = redir->next;
		free(redir);
		redir = next;
	}
}

t_command	*go_to_next_cmd(t_command *cmd)
{
	cmd = cmd->next;
	while (cmd && cmd->purpose != DELIM && cmd->purpose != CMD_DELIM)
		cmd = cmd->next;
	if (!cmd || cmd->purpose == CMD_DELIM)
		return (cmd);
	return (cmd->next);
}

void	exec_cleaner(t_process_cmd cmd_processing)
{
	free(cmd_processing.cmd);
	free_redirs(cmd_processing.redir);
	if (cmd_processing.cmd_name)
		free(cmd_processing.cmd_name);
}

void	close_pipes(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
}
