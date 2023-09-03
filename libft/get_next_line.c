/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:11:09 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/04 00:01:24 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*go_next_line(char *buf)
{
	char	*new_buffer;
	int		i_end_line;
	int		i_end;
	int		i;

	i_end_line = ft_strchr_int(buf, '\n');
	if (buf[i_end_line] == '\0')
	{
		free(buf);
		return (0);
	}
	i_end = ft_strchr_int(buf, '\0');
	new_buffer = (char *)ft_calloc(i_end - i_end_line, sizeof (char));
	i = 0;
	while (buf[i_end_line + i + 1])
	{
		new_buffer[i] = buf[i_end_line + i + 1];
		i++;
	}
	new_buffer[i] = buf[i_end_line + i + 1];
	free(buf);
	return (new_buffer);
}

static char	*get_line_buf(char *buf)
{
	char	*line;
	int		i;
	int		to_calloc;
	int		index_eol;
	int		eol_jump;

	index_eol = ft_strchr_int(buf, '\n');
	eol_jump = 0;
	if (buf[index_eol] == '\n')
		eol_jump = 1;
	to_calloc = index_eol + 1 + eol_jump;
	line = (char *)ft_calloc(to_calloc, sizeof (char));
	if (line == 0)
		return (0);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (eol_jump)
		line[i] = '\n';
	return (line);
}

static char	*str_append(char *temp, char *buf)
{
	char	*dest;

	dest = ft_strjoin(buf, temp);
	free(buf);
	return (dest);
}

static char	*read_file(int fd, char *buf)
{
	int		read_ok;
	char	*temp;

	if (!buf)
		buf = (char *)ft_calloc(1, sizeof (char));
	temp = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof (char));
	if (buf == 0 || temp == 0)
		return (free_buffers(buf, temp, 0));
	read_ok = 1;
	while (read_ok)
	{
		ft_bzero(temp, BUFFER_SIZE);
		read_ok = read(fd, temp, BUFFER_SIZE);
		if (read_ok == -1 || (buf[0] == 0 && read_ok == 0))
			return (free_buffers(buf, temp, 0));
		else if (read_ok == 0)
			break ;
		buf = str_append(temp, buf);
		if (buf == 0)
			return (free_buffers(buf, temp, 0));
		if (read_ok < BUFFER_SIZE || (buf[ft_strchr_int(buf, '\n')] == '\n'))
			break ;
	}
	free(temp);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	buffer = read_file(fd, buffer);
	if (buffer == 0)
		return (0);
	line = get_line_buf(buffer);
	if (line == 0)
		return (0);
	buffer = go_next_line(buffer);
	return (line);
}
