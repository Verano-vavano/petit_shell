/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:05:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/03 23:58:51 by hdupire          ###   ########.fr       */
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
	{
		temp2 = ft_strjoin(temp, cmd->content + se[0] + se[1] + 1);
		free(temp);
		if (!temp2)
			return ;
		free(cmd->content);
		cmd->content = temp2;
		return ;
	}
	temp2 = ft_strjoin(temp, to_merge->content);
	free(temp);
	if (!temp2)
		return ;
	temp = ft_strjoin(temp2, cmd->content + se[0] + se[1] + 1);
	free(temp2);
	if (!temp)
		return ;
	free(cmd->content);
	cmd->content = temp;
}

static void	merge_it(t_command *cmd, t_command *to_merge, int *se)
{
	t_command	*now;
	t_command	*end;
	char		*temp;
	char		*temp2;
	char		*org;

	if (!to_merge->next)
		return (handle_one(cmd, to_merge, se));
	org = cmd->content;
	now = to_merge->next;
	if (to_merge->content)
	{
		temp = ft_strndup(org, se[0]);
		if (!temp)
			return ;
		temp2 = ft_strjoin(temp, to_merge->content);
		if (!temp2)
			return ;
		free(temp);
		free(to_merge->content);
		free(to_merge);
		cmd->content = temp2;
	}
	end = cmd->next;
	cmd->next = now;
	while (now && now->next)
		now = now->next;
	temp = ft_strdup(org + se[0] + se[1] + 1);
	if (!temp)
		return ;
	temp2 = ft_strjoin(now->content, temp);
	free(temp);
	free(now->content);
	now->content = temp2;
	now->next = end;
	if (to_merge->content)
		free(org);
}

static int	search_next_ifs(char *newer, char *ifs)
{
	int	i;

	i = 0;
	while (newer[i])
	{
		if (ft_strchr(ifs, newer[i]))
			return (i);
		i++;
	}
	return (i);
}

static t_command	*split_it(char *newer, char *ifs)
{
	t_command	*to_merge;
	t_command	*now;
	int			i;
	int			to_dup;

	to_merge = ft_calloc(1, sizeof (t_command));
	if (!to_merge)
		return (0);
	to_merge->purpose = COMMAND;
	now = to_merge;
	i = 0;
	while (newer[i])
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

static char	*get_ifs(t_env *env)
{
	char	*ifs;
	char	**temp;

	if (env_contain("IFS", env))
	{
		temp = env_getval("IFS", env);
		if (!temp || !(*temp))
			ifs = ft_calloc(1, sizeof (char));
		else
			ifs = ft_strdup(temp[0]);
	}
	else
		ifs = ft_strdup(" \t\n");
	return (ifs);
}

void	word_split(t_command *cmd, char *newer, int *se, t_env *env)
{
	char		*ifs;
	t_command	*to_merge;

	ifs = get_ifs(env);
	if (!ifs)
		return ;
	to_merge = split_it(newer, ifs);
	free(ifs);
	merge_it(cmd, to_merge, se);
}
