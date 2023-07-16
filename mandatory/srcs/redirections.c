/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:23:40 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/16 15:28:52 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	dup_redir(t_redir_pipe *redir)
{
	if (redir->fd_read != -1)
		dup2(redir->fd_read, redir->fd_end);
	if (redir->fd_write != -1)
		dup2(redir->fd_write, redir->fd_end);
}

void	perform_redirections(t_process_cmd *cmd)
{
	bool			is_in_read_duped;
	bool			is_out_write_duped;
	t_redir_pipe	*redir;

	is_in_read_duped = 0;
	is_out_write_duped = 0;
	redir = cmd->redir;
	while (redir)
	{
		is_in_read_duped = (is_in_read_duped
			|| (redir->fd_end == STDIN_FILENO && redir->fd_read != -1));	
		is_out_write_duped = (is_out_write_duped
			|| (redir->fd_end == STDIN_FILENO && redir->fd_write != -1));	
		dup_redir(redir);
		redir = redir->next;
	}
}
