/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:31:39 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/29 19:22:36 by hdupire          ###   ########.fr       */
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
		if (cmd->purpose == HERE_DOC_DELIM || cmd->purpose == HERE_STRING)
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

static void	write_heredoc(int fd, char *eof, t_env *env)
{
	char	*line;
	int		lines;

	eof = quote_removal(ft_strdup(eof));
	lines = 1;
	while (g_sig_rec != SIGINT)
	{
		line = new_prompt(2, env);
		if (!line)
		{
			warning_heredoc_eof(lines, eof);
			break ;
		}
		line[ft_strchr_int(line, '\n')] = 0;
		if (!ft_strcmp(line, eof))
		{
			free(line);
			break ;
		}
		line[ft_strchr_int(line, '\n')] = '\n';
		write(fd, line, ft_strlen(line));
		free(line);
		lines++;
	}
	free(eof);
}

static int	heredoc_child(int fd, char *eof, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		write_heredoc(fd, eof, env);
		exit(0);
	}
	while (waitpid(pid, 0, WNOHANG) == 0)
	{
		if (g_sig_rec == SIGINT)
		{
			kill(pid, SIGINT);
			printf("\n");
			g_sig_rec = 0;
			return (130);
		}
		continue ;
	}
	return (1);
}

static int	create_heredoc(int index, t_command *cmd, t_env *env)
{
	int		fd_heredoc;

	fd_heredoc = get_heredoc_file(index, WRITE);
	if (fd_heredoc <= 0)
		return (1);
	if (cmd->purpose == HERE_DOC_DELIM)
	{
		if (!heredoc_child(fd_heredoc, cmd->content, env))
			return (1);
	}
	else
	{
		cmd->content = quote_removal(cmd->content);
		write(fd_heredoc, cmd->content, ft_strlen(cmd->content));
		write(fd_heredoc, "\n", 1);
	}
	close(fd_heredoc);
	return (0);
}

int	here_doc(t_command *cmd, t_env *env)
{
	int	i;

	i = 0;
	while (cmd->next)
	{
		if (cmd->purpose == HERE_DOC_DELIM || cmd->purpose == HERE_STRING)
		{
			create_heredoc(i, cmd, env);
			i++;
		}
		cmd = cmd->next;
	}
	if (cmd->purpose == HERE_DOC_DELIM || cmd->purpose == HERE_STRING)
		create_heredoc(i, cmd, env);
	return (0);
}
