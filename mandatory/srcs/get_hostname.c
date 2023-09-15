/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hostname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:25:00 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/15 17:31:17 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static bool	read_from_host(char *name)
{
	int	fd;
	int	readed;

	fd = open("/proc/sys/kernel/hostname", O_RDONLY);
	if (fd == -1)
		return (1);
	readed = read(fd, name, 2048);
	if (readed == -1)
	{
		close(fd);
		return (1);
	}
	name[readed - (name[readed - 1] == '\n')] = 0;
	close(fd);
	return (0);
}

char	*get_hostname(char *name, t_env *env)
{
	if (read_from_host(name) == 0)
		return (name);
	return (env_getval("HOSTNAME", env));
}
