/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 22:05:19 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/10 22:39:01 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

bool	is_chr(char *path)
{
	struct stat	file_stat;

	if (lstat(path, &file_stat) == 0)
		return (S_ISCHR(file_stat.st_mode));
	return (false);
}

bool	is_fifo(char *path)
{
	struct stat	file_stat;

	if (lstat(path, &file_stat) == 0)
		return (S_ISFIFO(file_stat.st_mode));
	return (false);
}

bool	is_sock(char *path)
{
	struct stat	file_stat;

	if (lstat(path, &file_stat) == 0)
		return (S_ISSOCK(file_stat.st_mode));
	return (false);
}

bool	is_gid(char *path)
{
	struct stat	file_stat;

	if (lstat(path, &file_stat) == 0)
		return (file_stat.st_mode & S_ISGID);
	return (false);
}

bool	is_uid(char *path)
{
	struct stat	file_stat;

	if (lstat(path, &file_stat) == 0)
		return (file_stat.st_mode & S_ISUID);
	return (false);
}
