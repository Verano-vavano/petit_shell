/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tilde.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:09:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/19 21:52:49 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	*get_from_passwd(char *username)
{
	char	*line;
	char	**split_line;
	int		fd_passwd;

	fd_passwd = open("/etc/passwd", O_RDONLY);
	if (fd_passwd < 0)
		return (0);
	line = get_next_line(fd_passwd);
	while (line && ft_strncmp(line, username, ft_strlen(username)))
	{
		if (line)
			free(line);
		line = get_next_line(fd_passwd);
	}
	close(fd_passwd);
	if (!line)
		return (0);
	split_line = ft_split(line, ':');
	if (!split_line)
		return (0);
	free(line);
	line = ft_strdup(split_line[5]);
	free_char_etoile_etoile(split_line);
	return (line);
}

char	*get_home(t_env *env)
{
	char	*home;
	char	*username;

	home = NULL;
	username = ft_calloc(257, sizeof (char));
	if (!username)
		return (0);
	get_username(username, env);
	if (!username)
		return (0);
	if (!access("/etc/passwd", R_OK))
		home = get_from_passwd(username);
	if (!home)
		home = ft_strjoin("/Users/", username);
	free(username);
	if (!home)
		return (0);
	return (home);
}
