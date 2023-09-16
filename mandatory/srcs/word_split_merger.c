/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split_merger.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:22:41 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/16 18:23:31 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	change_content(t_command *cmd, t_command *to_merge, char *cnt)
{
	free(cmd->content);
	free(to_merge);
	cmd->content = cnt;
}

static void	handle_one(t_command *cmd, t_command *to_merge, int *se)
{
	char	*temp;
	char	*temp2;

	temp = ft_strndup(cmd->content, se[0]);
	if (!temp)
		return ;
	if (!to_merge->content)
		temp2 = ft_strjoin(temp, cmd->content + se[0] + se[1] + 1);
	else
		temp2 = ft_strjoin(temp, to_merge->content);
	free(temp);
	if (!temp2)
		return ;
	if (!to_merge->content)
		return (change_content(cmd, to_merge, temp2));
	temp = ft_strjoin(temp2, cmd->content + se[0] + se[1] + 1);
	free(temp2);
	if (!temp)
		return ;
	free(cmd->content);
	cmd->content = temp;
	free(to_merge->content);
	free(to_merge);
}

static void	change_to_merge(t_command *cmd, t_command *to_merge, int *se)
{
	char		*temp;
	char		*temp2;

	if (to_merge->content)
	{
		temp = ft_strndup(cmd->content, se[0]);
		if (!temp)
			return ;
		temp2 = ft_strjoin(temp, to_merge->content);
		if (!temp2)
			return ;
		free(temp);
		free(to_merge->content);
		cmd->content = temp2;
	}
	if (to_merge)
		free(to_merge);
}

static char	*get_content_merger(char *org, int *se, t_command *now)
{
	char		*temp;
	char		*temp2;

	temp = ft_strdup(org + se[0] + se[1] + 1);
	if (!temp)
		return (0);
	temp2 = ft_strjoin(now->content, temp);
	free(temp);
	return (temp2);
}

void	merge_it(t_command *cmd, t_command *to_merge, int *se)
{
	t_command	*now;
	t_command	*end;
	char		*temp;
	bool		free_org;
	char		*org;

	if (!to_merge->next)
		return (handle_one(cmd, to_merge, se));
	org = cmd->content;
	now = to_merge->next;
	free_org = (to_merge && to_merge->content);
	change_to_merge(cmd, to_merge, se);
	end = cmd->next;
	cmd->next = now;
	while (now && now->next)
		now = now->next;
	temp = get_content_merger(org, se, now);
	if (!temp)
		return ;
	free(now->content);
	now->next = end;
	now->content = temp;
	if (free_org)
		free(org);
}
