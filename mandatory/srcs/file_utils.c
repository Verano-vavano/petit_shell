/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:27:44 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/10 22:00:20 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

bool	is_dir(char *path)
{
	struct stat	file_stat;

	if (lstat(path, &file_stat) == 0)
		return (S_ISDIR(file_stat.st_mode));
	return (false);
}

bool	is_lnk(char *path)
{
	struct stat	file_stat;

	if (lstat(path, &file_stat) == 0)
		return (S_ISLNK(file_stat.st_mode));
	return (false);
}

bool	is_blk(char *path)
{
	struct stat	file_stat;

	if (lstat(path, &file_stat) == 0)
		return (S_ISBLK(file_stat.st_mode));
	return (false);
}

bool	is_reg(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == 0)
		return (S_ISREG(file_stat.st_mode));
	return (false);
}

bool	is_empty_file(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == 0)
		return (file_stat.st_size > 0);
	return (false);
}
