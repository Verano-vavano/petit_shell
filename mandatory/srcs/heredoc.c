/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:31:39 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/04 17:44:11 by hdupire          ###   ########.fr       */
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

static int	create_heredoc(int index)
{
	int		fd_heredoc;
	char	*itoaed;
	char	*file_name;

	itoaed = ft_itoa(index);
	file_name = ft_strjoin(TEMP, itoaed);
	if (access(file_name, F_OK))
		unlink(file_name);
	fd_heredoc = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd_heredoc <= 0)
		return (1);
	free(itoaed);
	free(file_name);
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
			create_heredoc(i);
			i++;
		}
		cmd = cmd->next;
	}
	if (cmd->purpose == HERE_DOC_DELIM)
		create_heredoc(i);
	return (0);
}
