/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opening.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:15:27 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/08 15:54:29 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	open_write_file(t_command *cmd, t_redir_pipe *redir)
{
	char	*s;

	s = cmd->content;
	if (redir->opened_write)
		close(redir->fd_write);
	redir->opened_write = 1;
	if (cmd->purpose == OUT_FILE || cmd->purpose == IN_OUT_FILE)
		redir->fd_write = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (cmd->purpose == OUT_FILE_APP)
		redir->fd_write = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	return (redir->fd_write == -1);
}

int	open_read_file(t_command *cmd, t_redir_pipe *redir, int hd)
{
	redir->here_string = 0;
	if (redir->opened_read)
		close(redir->fd_read);
	redir->opened_read = 1;
	if (cmd->purpose == IN_FILE || cmd->purpose == IN_OUT_FILE)
	{
		redir->fd_read = open(cmd->content, O_RDONLY);
		if (redir->fd_read == -1)
		{
			perror(cmd->content);
			return (1);
		}
		redir->opened_read = 1;
	}
	else if (cmd->purpose == HERE_DOC_DELIM || cmd->purpose == HERE_STRING)
		redir->fd_read = get_heredoc_file(hd, READ);
	if (cmd->purpose != IN_FILE && cmd->purpose != IN_OUT_FILE)
		redir->opened_read = 0;
	return (0);
}
