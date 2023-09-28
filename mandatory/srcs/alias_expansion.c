/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:20:53 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/28 21:19:06 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static t_alias	*get_alias(char *content, t_alias *alias)
{
	while (alias)
	{
		if (!ft_strcmp(content, alias->cmd))
			return (alias);
		alias = alias->next;
	}
	return (0);
}

static t_command	*smol_split(char *s)
{
	t_command	*to_ret;
	t_command	*now;
	int			len_arg;

	to_ret = ft_calloc(1, sizeof (t_command));
	if (!to_ret)
		return (0);
	now = to_ret;
	len_arg = ft_strlen_arg(s, 0);
	while (*s && len_arg)
	{
		now->content = ft_strndup(s, len_arg);
		if (!now->content)
		{
			free_command(to_ret);
			return (0);
		}
		now->purpose = COMMAND;
		if (check_assign(now->content))
			now->purpose = VAR_ASSIGN;
		if (!s[len_arg])
			break ;
		s += len_arg + 1;
		len_arg = ft_strlen_arg(s, 0);
		if (*s && len_arg)
		{
			now->next = ft_calloc(1, sizeof (t_command));
			if (!now->next)
			{
				free_command(to_ret);
				return (0);
			}
			now = now->next;
		}
	}
	return (to_ret);
}

static void	perform_alias_exp(t_command *cmd, t_tool *tool)
{
	t_alias		*replacer;
	t_command	*splited;
	t_command	*end;
	char		*newer;

	replacer = get_alias(cmd->content, tool->alias_start);
	if (!replacer)
		return ;
	newer = ft_strdup(replacer->replacer);
	if (!newer)
		return ;
	splited = smol_split(newer);
	free(newer);
	if (!splited)
		return;
	free(cmd->content);
	cmd->content = splited->content;
	cmd->purpose = splited->purpose;
	end = cmd->next;
	cmd->next = splited->next;
	while (cmd->next)
		cmd = cmd->next;
	cmd->next = end;
	free(splited);
}

void	alias_expansion(t_command *cmd, t_tool *tool)
{
	bool	changed;

	while (cmd && cmd->purpose == VAR_ASSIGN)
	{
		perform_alias_exp(cmd, tool);
		cmd = cmd->next;
	}
	changed = false;
	while (cmd && !changed)
	{
		perform_alias_exp(cmd, tool);
		changed = (cmd->purpose != VAR_ASSIGN);
		if (cmd->purpose == VAR_ASSIGN)
			cmd = cmd->next;
	}
}
