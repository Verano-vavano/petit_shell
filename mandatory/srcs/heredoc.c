/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:31:39 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/05 15:57:53 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
/*
void	get_text(t_piping *p, int *pipe)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		line[ft_strchr_int(line, '\n')] = 0;
		if (!(ft_strcmp(line, p->limit)))
			break ;
		line[ft_strchr_int(line, '\n')] = '\n';
		write(*pipe, line, ft_strlen(line));
		free(line);
	}
	free(line);
}*/

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

	line = ft_calloc(BUFFER_SIZE + 1, sizeof (char));
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
	char	*itoaed;
	char	*file_name;

	itoaed = ft_itoa(index);
	file_name = ft_strjoin(TEMP, itoaed);
	if (!access(file_name, F_OK))
		unlink(file_name);
	fd_heredoc = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd_heredoc <= 0)
		return (1);
	free(itoaed);
	free(file_name);
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
