/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:40:10 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/11 16:00:45 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static t_redir_pipe	*get_redir_struct(t_redir_pipe *redir, int fd)
{
	if (!redir)
	{
		redir = ft_calloc(1, sizeof (t_redir_pipe));
		if (!redir)
			return (redir);
		redir->fd_read = -1;
		redir->fd_write = -1;
		redir->fd_end = fd;
		return (redir);
	}
	while (redir->next)
	{
		if (redir->fd_end == fd)
			return (redir);
		redir = redir->next;
	}
	if (redir->fd_end == fd)
		return (redir);
	redir->next = ft_calloc(1, sizeof (t_redir_pipe));
	if (!redir->next)
		return (0);
	redir->next->fd_read = -1;
	redir->next->fd_write = -1;
	redir->next->fd_end = fd;
	return (redir->next);
}

static int	get_redir_from(enum e_cmd_part redir, char *s, int len)
{
	char	*redir_from;
	int		fd;

	if (len <= 7 && len > 0)
	{
		redir_from = ft_strndup(s, len);
		if (redir_from)
		{
			fd = ft_atoi(redir_from);
			free(redir_from);
			return (fd);
		}
	}
	if (redir == IN_FILE || redir == HERE_DOC_DELIM || redir == IN_OUT_FILE
		|| redir == HERE_STRING)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

static int	handle_files(t_process_cmd *cmd_p, t_command *cmd, int hd)
{
	int				i1;
	int				i2;
	int				redir_from_fd;
	t_redir_pipe	*redir;

	i1 = ft_strchr_int(cmd->content, '<');
	i2 = ft_strchr_int(cmd->content, '>');
	if (i2 < i1)
		i1 = i2;
	redir_from_fd = get_redir_from(cmd->next->purpose, cmd->content, i1);
	redir = get_redir_struct(cmd_p->redir, redir_from_fd);
	open_redir_files(cmd->next, redir, hd);
	if (cmd_p->redir == 0)
		cmd_p->redir = redir;
	return (hd + (cmd->next->purpose == HERE_DOC_DELIM
			|| cmd->next->purpose == HERE_STRING));
}

static int	count_args(t_command *cmd)
{
	int	n;

	n = 0;
	while (cmd && cmd->purpose != CMD_DELIM && cmd->purpose != DELIM)
	{
		if (cmd->purpose == COMMAND)
			n++;
		cmd = cmd->next;
	}
	return (n);
}

int	get_cmd(t_process_cmd *cmd_processing, t_command *cmd, int *hd_no)
{
	int	n_args;
	int	here_docs;
	int	i;

	n_args = count_args(cmd);
	cmd_processing->cmd = ft_calloc(n_args + 1, sizeof (char *));
	if (cmd_processing->cmd == 0)
		return (1);
	i = 0;
	here_docs = *hd_no;
	while (cmd && cmd->purpose != CMD_DELIM && cmd->purpose != DELIM)
	{
		if (cmd->purpose == COMMAND)
		{
			cmd_processing->cmd[i] = cmd->content;
			i++;
		}
		else if (cmd->purpose == REDIR_ID)
			here_docs = handle_files(cmd_processing, cmd, here_docs);
		cmd = cmd->next;
	}
	*hd_no = here_docs;
	return (0);
}
