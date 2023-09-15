/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:05:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/15 12:37:07 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

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
	{
		free(cmd->content);
		free(to_merge);
		cmd->content = temp2;
		return ;
	}
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

static void	merge_it(t_command *cmd, t_command *to_merge, int *se)
{
	t_command	*now;
	t_command	*end;
	bool		free_org;
	char		*temp;
	char		*temp2;
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
	temp = ft_strdup(org + se[0] + se[1] + 1);
	if (!temp)
		return ;
	temp2 = ft_strjoin(now->content, temp);
	now->next = end;
	free(temp);
	if (!temp2)
		return ;
	free(now->content);
	now->content = temp2;
	if (free_org)
		free(org);
}

static t_command	*split_it(char *newer, char *ifs)
{
	t_command	*to_merge;
	t_command	*now;
	int			i;
	int			to_dup;

	to_merge = ft_calloc(1, sizeof (t_command));
	now = to_merge;
	i = 0;
	while (now && newer[i])
	{
		to_dup = search_next_ifs(newer + i, ifs);
		now->content = ft_strndup(newer + i, to_dup);
		i += to_dup;
		while (newer[i] && ft_strchr(ifs, newer[i]))
			i++;
		if (newer[i] && now->content)
		{
			now->next = ft_calloc(1, sizeof (t_command));
			now = now->next;
			if (now)
				now->purpose = COMMAND;
		}
	}
	return (to_merge);
}

int	word_split(t_command *cmd, char *newer, int *se, t_env *env)
{
	char		*ifs;
	t_command	*to_merge;

	ifs = get_ifs(env);
	if (!ifs)
		return (0);
	to_merge = split_it(newer, ifs);
	if (to_merge)
		to_merge->purpose = cmd->purpose;
	else
		return (0);
	free(ifs);
	if (to_merge->next && cmd->purpose >= IN_FILE && cmd->purpose <= IN_OUT_FILE)
	{
		free_command(to_merge);
		return (ambiguous_error(cmd->content));
	}
	merge_it(cmd, to_merge, se);
	return (0);
}
