/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 07:48:54 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/27 12:39:23 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	sort_lf(t_list_file *lf)
{
	t_list_file	*temp;
	char		*temp_str;
	bool		swaped;

	swaped = true;
	while (swaped)
	{
		swaped = false;
		temp = lf;
		while (temp && temp->next)
		{
			if (ft_strcmp(temp->content, temp->next->content) > 0)
			{
				temp_str = temp->content;
				temp->content = temp->next->content;
				temp->next->content = temp_str;
				swaped = true;
			}
			temp = temp->next;
		}
	}
}

static void	add_lf_cmd(t_command *cmd, t_list_file *lf)
{
	t_command	*new;
	bool		start;

	start = true;
	while (lf && lf->content)
	{
		if (start)
		{
			free(cmd->content);
			start = false;
		}
		else
		{
			new = ft_calloc(1, sizeof (t_command));
			if (!new)
				return ;
			new->next = cmd->next;
			cmd->next = new;
			new->purpose = COMMAND;
			cmd = cmd->next;
		}
		cmd->content = ft_strdup(lf->content);
		lf = lf->next;
	}
}

static void	free_lf(t_list_file *lf)
{
	t_list_file *temp;

	while (lf)
	{
		temp = lf->next;
		free(lf->content);
		free(lf);
		lf = temp;
	}
}

static void	add_to_lf(char *file, t_list_file *lf)
{
	if (lf->content != 0)
	{
		while (lf->next)
			lf = lf->next;
		lf->next = ft_calloc(1, sizeof (t_list_file));
		lf = lf->next;
	}
	if (!lf)
		return ;
	lf->content = ft_strdup(file);
}

static int	get_path_star_fe(char *cnt)
{
	char	quoted;
	int		i;
	int		last_s;

	i = 0;
	last_s = 0;
	quoted = 0;
	while (cnt[i] && (quoted || cnt[i] != '*'))
	{
		quoted = is_quoted(cnt, i, quoted);
		if (cnt[i] == '/' && !quoted)
			last_s = i;
		i++;
	}
	return (last_s);
}

static bool	check_end(char *qr_match, char *file)
{
	int	i;
	int	j;

	i = ft_strlen(file) - 1;
	j = ft_strchr_int(qr_match, '/') - 1;
	while (qr_match[j] != '*')
	{
		if (qr_match[j] != file[i])
			return (false);
		i--;
		j--;
	}
	return (true);
}

static void	move_to_next(char *qr_match, char *file, int *i, int *j)
{
	char	*cpy;
	char	*finder;

	cpy = ft_strndup(qr_match + *j + 1, unquote_search(qr_match + *j + 1, '*'));
	if (cpy)
	{
		finder = ft_strstr(file, cpy);
		(*j)++;
		if (finder)
			(*i) += (finder - (file + *i));
		else
			(*i) = -1;;
		free(cpy);
		return ;
	}
	(*i)++;
	(*j)++;
}

static bool	is_valid_fe(char *file, char *matcher)
{
	int		i;
	int		j;
	char	*qr_match;

	i = 0;
	j = 0;
	qr_match = quote_removal(matcher);
	if (qr_match == 0)
		return (false);
	if (qr_match[0] == '*' && file[0] == '.')
		return (false);
	while (file[i] && qr_match[j] && !(qr_match[j] == '/'))
	{
		if (qr_match[j] == '*' && qr_match[j + 1 + unquote_search(qr_match + j + 1, '*')]
			&& unquote_search(qr_match + j + 1, '/') > unquote_search(qr_match + j + 1, '*'))
			move_to_next(qr_match, file, &i, &j);
		else if (qr_match[j] == '*')
			return (check_end(qr_match + j, file));
		if (i == -1 || (qr_match[j] != '/' && qr_match[j] != file[i]))
			return (false);
		i++;
		j++;
	}
	return (true);
}

static void	get_all_valid_files(t_command *cmd, int index, t_list_file *lf)
{
	char			*path;
	DIR				*dir;
	struct dirent	*file;
	char			*file_n_path;

	path = 0;
	if (index != 0)
		path = ft_strndup(cmd->content, index);
	if (index == 0 || !path || !is_dir(path))
		dir = opendir("./");
	else if (path && is_dir(path))
		dir = opendir(path);
	file = readdir(dir);
	while (file)
	{
		if (is_valid_fe(file->d_name, cmd->content + index))
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
	if (path)
		free(path);
	closedir(dir);
}

static t_list_file	*remove_flf(t_list_file *act, t_list_file *lf)
{
	t_list_file	*lf2;

	if (act == lf)
	{
		lf = lf->next;
		free(act->content);
		free(act);
		return (lf);
	}
	lf2 = lf;
	while (lf2->next != act)
		lf2 = lf2->next;
	if (act->next)
		lf2->next = act->next;
	else
		lf2->next = 0;
	free(act->content);
	free(act);
	return (lf);
}

static t_list_file	*check_all_subfiles(t_command *cmd, int index, t_list_file *lf, t_list_file *nlf)
{
	DIR				*dir;
	struct dirent	*file;
	char			*file_n_path;
	t_list_file		*temp;
	t_list_file		*next;

	temp = lf;
	while (temp)
	{
		dir = opendir(temp->content);
		file = readdir(dir);
		while (file)
		{
			if (is_valid_fe(file->d_name, cmd->content + index))
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
		closedir(dir);
		next = temp->next;
		temp = next;
	}
	return (nlf);
}

static t_list_file	*get_all_vf_flf(t_command *cmd, int index, int last, t_list_file *lf)
{
	char			*temp;
	char			*path;
	t_list_file		*act;
	t_list_file		*next_cpy;
	t_list_file		*new_lf;

	path = ft_strndup(cmd->content + last, index - last);
	if (!path)
		return (0);
	act = lf;
	while (act)
	{
		temp = ft_strjoin(act->content, path);
		if (!is_dir(temp))
		{
			next_cpy = act->next;
			lf = remove_flf(act, lf);
			act = next_cpy;
			free(temp);
		}
		else
		{
			free(act->content);
			act->content = temp;
			act = act->next;
		}
	}
	if (!lf || !(lf->content))
		return (0);
	else if (!(cmd->content[index]))
		return (lf);
	new_lf = ft_calloc(1, sizeof (t_list_file));
	if (!new_lf)
	{
		free_lf(lf);
		return (0);
	}
	new_lf = check_all_subfiles(cmd, index, lf, new_lf);
	free_lf(lf);
	free(path);
	return (new_lf);
}

static void	perform_file_exp(t_command *cmd)
{
	t_list_file		*lf;
	int				index;
	bool			not_ended;
	bool			start;
	int				last;

	index = 0;
	lf = ft_calloc(1, sizeof (t_list_file));
	if (!lf)
		return ;
	not_ended = true;
	start = true;
	while (not_ended)
	{
		index += get_path_star_fe(cmd->content + index);
		index += (cmd->content[index] == '/');
		if (start)
		{
			get_all_valid_files(cmd, index, lf);
			if (!(lf->content))
			{
				free(lf);
				return ;
			}
		}
		else
			lf = get_all_vf_flf(cmd, index, last, lf);
		not_ended = cmd->content[index + unquote_search(cmd->content + index, '/')] != '\0';
		index += unquote_search(cmd->content + index, '/');
		last = index;
		start = false;
	}
	sort_lf(lf);
	add_lf_cmd(cmd, lf);
	free_lf(lf);
}

static void	perform_quest_expand(t_command *cmd)
{
	DIR				*dir;
	struct dirent	*file;
	t_list_file		*lf;

	lf = ft_calloc(1, sizeof (t_list_file));
	if (!lf)
		return ;
	dir = opendir("./");
	file = readdir(dir);
	while (file)
	{
		if (ft_strlen(file->d_name) == 1 && file->d_name[0] != '.')
			add_to_lf(file->d_name, lf);
		file = readdir(dir);
	}
	closedir(dir);
	sort_lf(lf);
	add_lf_cmd(cmd, lf);
	free_lf(lf);
}

void	filename_expansion(t_command *cmd)
{
	signal(SIGINT, SIG_DFL); // TO REM
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		if (cmd->purpose == COMMAND && ft_strchr(cmd->content, '*'))
			perform_file_exp(cmd);
		else if (cmd->purpose == COMMAND && ft_strlen(cmd->content) == 1 && cmd->content[0] == '?')
			perform_quest_expand(cmd);
		cmd = cmd->next;
	}
}
