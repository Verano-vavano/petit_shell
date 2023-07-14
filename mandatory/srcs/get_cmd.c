/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:40:10 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/14 13:54:54 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
/*
static void	handle_infile(t_process_cmd *cmd_p, t_command *cmd, int hd)
{
	char	*here_doc_file;
	char	*no_hd;

	if (cmd->purpose == IN_FILE || cmd->purpose == IN_OUT_FILE)
		cmd_p->fd_in = open(cmd->content, O_RDONLY);
	else if (cmd->purpose == HERE_DOC_DELIM)
	{
		no_hd = ft_itoa(hd);
		if (!no_hd)
		{
			cmd_p->fd_in = -1;
			return ;
		}
		here_doc_file = ft_strjoin(TEMP, no_hd);
		free(no_hd);
		if (!here_doc_file)
		{
			cmd_p->fd_in = -1;
			return ;
		}
		cmd_p->fd_in = open(here_doc_file, O_RDONLY);
		free(here_doc_file);
	}
	else if (cmd->purpose == HERE_STRING)
		cmd_p->fd_in = -2;
}*/

static t_redir_pipe	*get_redir_struct(t_redir_pipe *redir)
{
	(void) redir;
	return (0);
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
	redir = get_redir_struct(cmd_p->redir);
	(void) cmd_p;
	return (hd + (cmd->next->purpose == HERE_DOC_DELIM));
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

int	get_cmd(t_process_cmd *cmd_processing, t_command *cmd)
{
	int	n_args;
	int	here_docs;
	int	i;

	n_args = count_args(cmd);
	cmd_processing->cmd = ft_calloc(n_args + 1, sizeof (char *));
	if (cmd_processing->cmd == 0)
		return (1);
	i = 0;
	here_docs = 0;
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
	free(cmd_processing->cmd);
	return (0);
}
