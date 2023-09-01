/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fe_subverif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:10:39 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/01 16:12:01 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	file_verif_loop(DIR *dir, char *cnt, char *path, t_lf *lf)
{
	struct dirent	*file;
	char			*file_n_path;

	file = readdir(dir);
	while (file)
	{
		if (is_valid_fe(file->d_name, cnt))
		{
			file_n_path = 0;
			if (path)
				file_n_path = ft_strjoin(path, file->d_name);
			if (file_n_path)
			{
				add_to_lf(file_n_path, lf);
				free(file_n_path);
			}
			else
				add_to_lf(file->d_name, lf);
		}
		file = readdir(dir);
	}
}

void	get_all_valid_files(t_command *cmd, int index, t_lf *lf)
{
	char			*path;
	DIR				*dir;

	path = 0;
	if (index != 0)
		path = ft_strndup(cmd->content, index);
	if (index == 0 || !path || !is_dir(path))
		dir = opendir("./");
	else if (path && is_dir(path))
		dir = opendir(path);
	file_verif_loop(dir, cmd->content + index, path, lf);
	if (path)
		free(path);
	closedir(dir);
}

static void	easier_subfile_loop(DIR *dir, char *cnt, t_lf *temp, t_lf *nlf)
{
	struct dirent	*file;
	char			*file_n_path;

	file = readdir(dir);
	while (file)
	{
		if (is_valid_fe(file->d_name, cnt))
		{
			file_n_path = ft_strjoin(temp->content, file->d_name);
			if (file_n_path)
			{
				add_to_lf(file_n_path, nlf);
				free(file_n_path);
			}
			else
				add_to_lf(file->d_name, nlf);
		}
		file = readdir(dir);
	}
}

t_lf	*check_subfiles(t_command *cmd, int index, t_lf *lf, t_lf *nlf)
{
	DIR				*dir;
	t_lf			*temp;
	t_lf			*next;

	temp = lf;
	while (temp)
	{
		dir = opendir(temp->content);
		easier_subfile_loop(dir, cmd->content + index, temp, nlf);
		closedir(dir);
		next = temp->next;
		temp = next;
	}
	return (nlf);
}
