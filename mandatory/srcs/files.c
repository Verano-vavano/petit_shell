/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:50:47 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/22 07:24:30 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	unlink_heredocs(t_command *cmd)
{
	int		i;
	char	*itoaed;
	char	*file_name;

	i = 0;
	while (cmd->content)
	{
		if (cmd->purpose == HERE_DOC_DELIM || cmd->purpose == HERE_STRING)
		{
			itoaed = ft_itoa(i);
			if (!itoaed)
				return ;
			file_name = ft_strjoin(TEMP, itoaed);
			free(itoaed);
			if (!file_name)
				return ;
			unlink(file_name);
			free(file_name);
			i++;
		}
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
}

void	close_files(t_redir_pipe *redir)
{
	while (redir)
	{
		if (redir->opened_read && redir->fd_read >= 0)
			close(redir->fd_read);
		if (redir->opened_write && redir->fd_write >= 0)
			close(redir->fd_write);
		redir = redir->next;
	}
}

static bool	is_valid_fd(long fd)
{
	struct stat	file_stat;

	if (fstat((int)fd, &file_stat) == -1)
		return (0);
	return (1);
}

static int	handle_fd_redir(t_command *cmd, t_redir_pipe *redir)
{
	long	fd;

	if (!is_all_num(cmd->next->content))
		return (1);
	if (ft_strlen(cmd->next->content) > 10)
		return (some_error("-1", "Bad file descriptor"));
	else if (cmd->next->content[0] == '-')
		return (some_error(cmd->next->content, "Bad file descriptor"));
	fd = ft_atol(cmd->next->content);
	if (fd > INT_MAX)
		return (some_error("-1", "Bad file descriptor"));
	else if (!is_valid_fd(fd))
		return (some_error(cmd->next->content, "Bad file descriptor"));
	if (cmd->next->purpose == IN_FILE)
	{
		redir->opened_read = 0;
		redir->fd_read = (int)fd;
	}
	else if (cmd->next->purpose == OUT_FILE)
	{
		redir->opened_write = 0;
		redir->fd_write = (int)fd;
	}
	return (0);
}

int	open_redir_files(t_command *cmd, t_redir_pipe *redir, int hd)
{
	if (cmd->content[0] == '&')
	{
		if (handle_fd_redir(cmd, redir))
			return (1);
		return (0);
	}
	if (cmd->purpose == IN_FILE || cmd->purpose == HERE_DOC_DELIM
		|| cmd->purpose == IN_OUT_FILE || cmd->purpose == HERE_STRING)
	{
		if (open_read_file(cmd, redir, hd))
			return (1);
	}
	if (cmd->purpose == OUT_FILE || cmd->purpose == OUT_FILE_APP
		|| cmd->purpose == IN_OUT_FILE)
	{
		if (open_write_file(cmd, redir))
			return (1);
	}
	return (0);
}
