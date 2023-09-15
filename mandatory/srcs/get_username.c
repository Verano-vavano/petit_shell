/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_username.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:08:49 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/15 17:09:50 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

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
	name[readed - 1] = '\0';
	close(pipes[0]);
	return (name);
}

char	*get_username(char *name, t_env *env)
{
	char	*username_get;

	whoami_get(name);
	if (name)
		return (name);
	username_get = env_getval("LOGNAME", env);
	if (username_get)
	{
		name = ft_strdup(username_get);
		return (name);
	}
	username_get = env_getval("USERNAME", env);
	if (!username_get)
		return (0);
	name = ft_strdup(username_get);
	return (name);
}
