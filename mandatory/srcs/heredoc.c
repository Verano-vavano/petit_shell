/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:31:39 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/15 18:09:19 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	get_heredoc_file(int hd, int mode)
{
	char	*itoaed;
	char	*filename;
	int		fd;

	itoaed = ft_itoa(hd);
	if (!itoaed)
		return (-1);
	filename = ft_strjoin(TEMP, itoaed);
	if (!filename)
		return (-1);
	free(itoaed);
	fd = 0;
	if (mode == READ)
		fd = open(filename, O_RDONLY);
	else if (mode == WRITE)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0666);
	free(filename);
	return (fd);
}

void	unlink_heredocs(t_command *cmd)
{
	int		i;
	char	*itoaed;
	char	*file_name;

	i = 0;
	while (cmd->content)
	{
		if (cmd->purpose == HERE_DOC_DELIM)
		{
			itoaed = ft_itoa(i);
			file_name = ft_strjoin(TEMP, itoaed);
			unlink(file_name);
			free(itoaed);
			free(file_name);
			i++;
		}
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
}

static void	write_heredoc(int fd, char *eof)
{
	char	*line;

	while (1)
	{
		line = readline(PS2);
		line[ft_strchr_int(line, '\n')] = 0;
		if (!ft_strcmp(line, eof))
		{
			free(line);
			break ;
		}
		line[ft_strchr_int(line, '\n')] = '\n';
		write(fd, line, ft_strlen(line));
		free(line);
	}
}

static int	create_heredoc(int index, char *eof)
{
	int		fd_heredoc;

	fd_heredoc = get_heredoc_file(index, WRITE);
	if (fd_heredoc <= 0)
		return (1);
	write_heredoc(fd_heredoc, eof);
	close(fd_heredoc);
	return (0);
}

int	here_doc(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->next)
	{
		if (cmd->purpose == HERE_DOC_DELIM)
		{
			create_heredoc(i, cmd->content);
			i++;
		}
		cmd = cmd->next;
	}
	if (cmd->purpose == HERE_DOC_DELIM)
		create_heredoc(i, cmd->content);
	return (0);
}
