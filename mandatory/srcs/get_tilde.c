/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tilde.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:09:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/26 13:43:57 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	*get_from_passwd(char *username)
{
	char	*line;
	char	**split_line;
	int		fd_passwd;

	fd_passwd = open("/etc/passwd", O_RDONLY);
	line = get_next_line(fd_passwd);
	while (line && ft_strncmp(line, username, ft_strlen(username)))
	{
		if (line)
			free(line);
		line = get_next_line(fd_passwd);
	}
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

static char	*whoami_get(char *name)
{
	pid_t	pid;
	int		readed;
	int		pipes[2];

	if (access("/usr/bin/whoami", X_OK) || pipe(pipes))
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid == 0)
	{
		close(pipes[0]);
		dup2(pipes[1], STDOUT_FILENO);
		execve("/usr/bin/whoami", (char *[]){"whoami", 0}, 0);
		return (0);
	}
	close(pipes[1]);
	waitpid(pid, 0, 0);
	readed = read(pipes[0], name, 256);
	if (readed == -1)
		return (0);
	name[readed - 1] = 0;
	close(pipes[0]);
	return (name);
}

static char	*find_username(char *name, t_env *env)
{
	char	**username_get;

	whoami_get(name);
	if (name)
		return (name);
	username_get = env_getval("LOGNAME", env);
	if (username_get)
	{
		name = ft_strdup(*username_get);
		return (name);
	}
	username_get = env_getval("USERNAME", env);
	if (!username_get)
		return (0);
	name = ft_strdup(*username_get);
	return (name);
}

char	*rescue_tilde_funk(t_env *env)
{
	char	*home;
	char	*username;

	username = ft_calloc(257, sizeof (char));
	if (!username)
		return (0);
	find_username(username, env);
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
