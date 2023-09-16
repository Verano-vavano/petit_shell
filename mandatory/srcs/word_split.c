/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:05:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/16 18:23:02 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

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
	if (to_merge->next && cmd->purpose >= IN_FILE
		&& cmd->purpose <= IN_OUT_FILE)
	{
		free_command(to_merge);
		return (ambiguous_error(cmd->content));
	}
	merge_it(cmd, to_merge, se);
	return (0);
}
