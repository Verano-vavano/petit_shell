/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_two_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:52:15 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/11 20:09:13 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

bool	files_ef(char *file1, char *file2)
{
	struct stat	file_stat1;
	struct stat	file_stat2;

	if (stat(file1, &file_stat1) == 0 && stat(file2, &file_stat2) == 0)
	{
		return (file_stat1.st_dev == file_stat2.st_dev
			&& file_stat1.st_ino == file_stat2.st_ino);
	}
	return (false);
}

bool	files_nt(char *file1, char *file2)
{
	struct stat	file_stat1;
	struct stat	file_stat2;

	if (access(file1, F_OK) == 0 && access(file2, F_OK) != 0)
		return (true);
	if (stat(file1, &file_stat1) == 0 && stat(file2, &file_stat2) == 0)
		return (file_stat1.st_mtime > file_stat2.st_mtime);
	return (false);
}

bool	files_ot(char *file1, char *file2)
{
	struct stat	file_stat1;
	struct stat	file_stat2;

	if (access(file2, F_OK) == 0 && access(file1, F_OK) != 0)
		return (true);
	if (stat(file1, &file_stat1) == 0 && stat(file2, &file_stat2) == 0)
		return (file_stat1.st_mtime < file_stat2.st_mtime);
	return (false);
}
