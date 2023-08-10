/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleepy_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:52:34 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 12:51:23 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

pid_t	sleepy_time(int level)
{
	pid_t	pid;
	float	sleeper;
	int		iter;
	char	*sleep_time;

	pid = fork();
	if (pid != 0)
		return (pid);
	sleeper = 0.5;
	iter = 0;
	while (iter < level || iter == 6)
	{
		sleeper /= 1.3;
		iter++;
	}
	sleep_time = ft_simple_ftoa(sleeper, 5);
	execve("/usr/bin/sleep", (char *[]){"sleep", sleep_time, 0}, 0);
	free(sleep_time);
	return (0);
}
