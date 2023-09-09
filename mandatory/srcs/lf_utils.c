/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:00:59 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/08 18:28:16 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	sort_lf(t_lf *lf)
{
	t_lf	*temp;
	char	*temp_str;
	bool	swaped;

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

void	add_lf_cmd(t_command *cmd, t_lf *lf, int purpose)
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
			new->purpose = purpose;
			cmd = cmd->next;
		}
		cmd->content = ft_strdup(lf->content);
		lf = lf->next;
	}
}

void	free_lf(t_lf *lf)
{
	t_lf	*temp;

	while (lf)
	{
		temp = lf->next;
		free(lf->content);
		free(lf);
		lf = temp;
	}
}

void	add_to_lf(char *file, t_lf *lf)
{
	if (lf->content != 0)
	{
		while (lf->next)
			lf = lf->next;
		lf->next = ft_calloc(1, sizeof (t_lf));
		lf = lf->next;
	}
	if (!lf)
		return ;
	lf->content = ft_strdup(file);
}

t_lf	*remove_flf(t_lf *act, t_lf *lf)
{
	t_lf	*lf2;

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
