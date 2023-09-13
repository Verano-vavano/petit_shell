/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 07:48:54 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/13 11:01:09 by tcharanc         ###   ########.fr       */
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
		not_end = cmd->content[index + usearch(cmd->content + index, '/')];
		index += usearch(cmd->content + index, '/');
		last = index;
	}
	return (lf);
}

static bool	perform_file_exp(t_command *cmd, int purpose)
{
	t_lf	*lf;

	lf = ft_calloc(1, sizeof (t_lf));
	if (!lf)
		return (false);
	lf = fe_mainloop(cmd, 0, lf, true);
	if (!lf)
		return (false);
	sort_lf(lf);
	if (purpose != COMMAND && lf->next && lf->next->content)
	{
		free_lf(lf);
		return (true);
	}
	add_lf_cmd(cmd, lf, purpose);
	free_lf(lf);
	return (false);
}

int	filename_expansion(t_command *cmd)
{
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		if (cmd->content[usearch(cmd->content, '*')]
			|| cmd->content[usearch(cmd->content, '?')])
		{
			if (cmd->purpose >= IN_FILE && cmd->purpose <= HERE_STRING && cmd->purpose != HERE_DOC_DELIM)
			{
				if (perform_file_exp(cmd, cmd->purpose))
					return (ambiguous_error(cmd->content));
			}
			else if (cmd->purpose == COMMAND)
				perform_file_exp(cmd, cmd->purpose);
		}
		cmd = cmd->next;
	}
	return (0);
}
