/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 07:48:54 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/01 16:12:05 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static t_lf	*loop_dir_ok(t_lf *lf, char *path)
{
	char	*temp;
	t_lf	*act;
	t_lf	*next_cpy;

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
	return (lf);
}

static t_lf	*get_all_vf_flf(t_command *cmd, int index, int last, t_lf *lf)
{
	char	*path;
	t_lf	*new_lf;

	path = ft_strndup(cmd->content + last, index - last);
	if (!path)
		return (0);
	lf = loop_dir_ok(lf, path);
	if (!lf || !(lf->content))
		return (0);
	else if (!(cmd->content[index]))
		return (lf);
	new_lf = ft_calloc(1, sizeof (t_lf));
	if (!new_lf)
	{
		free_lf(lf);
		return (0);
	}
	new_lf = check_subfiles(cmd, index, lf, new_lf);
	free_lf(lf);
	free(path);
	return (new_lf);
}

static t_lf	*fe_mainloop(t_command *cmd, int index, t_lf *lf, bool not_end)
{
	int	last;

	while (not_end)
	{
		index += get_path_star_fe(cmd->content + index);
		index += (cmd->content[index] == '/');
		if (!(lf->content))
		{
			get_all_valid_files(cmd, index, lf);
			if (!(lf->content))
			{
				free(lf);
				return (0);
			}
		}
		else
			lf = get_all_vf_flf(cmd, index, last, lf);
		not_end = cmd->content[index + usearch(cmd->content + index, '/')] != 0;
		index += usearch(cmd->content + index, '/');
		last = index;
	}
	return (lf);
}

static void	perform_file_exp(t_command *cmd)
{
	t_lf	*lf;

	lf = ft_calloc(1, sizeof (t_lf));
	if (!lf)
		return ;
	lf = fe_mainloop(cmd, 0, lf, true);
	if (!lf)
		return ;
	sort_lf(lf);
	add_lf_cmd(cmd, lf);
	free_lf(lf);
}

void	filename_expansion(t_command *cmd)
{
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		if (cmd->purpose == COMMAND
			&& (ft_strchr(cmd->content, '*') || ft_strchr(cmd->content, '?')))
			perform_file_exp(cmd);
		cmd = cmd->next;
	}
}
