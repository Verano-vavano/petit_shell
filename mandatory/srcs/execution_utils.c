/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:31:55 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/15 18:28:42 by hdupire          ###   ########.fr       */
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
