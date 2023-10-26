/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:20:53 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/26 14:58:56 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static t_command	*smol_split(char *s)
{
	t_command	*to_ret;
	t_command	*now;
	int			len_arg;

	to_ret = ft_calloc(1, sizeof (t_command));
	now = to_ret;
	len_arg = ft_strlen_arg(s, 0);
	while (now && *s && len_arg)
	{
		now->content = ft_strndup(s, len_arg);
		if (!now->content)
		{
			free_command(to_ret);
			return (0);
		}
		now->purpose = COMMAND;
		if (check_assign(now->content, false))
			now->purpose = VAR_ASSIGN;
		if (!s[len_arg])
			break ;
		s += len_arg + 1;
		len_arg = ft_strlen_arg(s, 0);
		now = al_add_new_command(s, len_arg, now, &to_ret);
	}
	return (to_ret);
}

static bool	perform_alias_exp(t_command *cmd, t_tool *tool)
{
	t_alias		*replacer;
	t_command	*splited;
	t_command	*end;
	char		*newer;

	replacer = get_alias(cmd->content, tool->alias_start);
	if (!replacer)
		return (false);
	newer = ft_strdup(replacer->replacer);
	if (!newer)
		return (false);
	splited = smol_split(newer);
	free(newer);
	if (!splited)
		return (false);
	free(cmd->content);
	cmd->content = splited->content;
	cmd->purpose = splited->purpose;
	end = cmd->next;
	cmd->next = splited->next;
	while (cmd->next)
		cmd = cmd->next;
	cmd->next = end;
	free(splited);
	return (true);
}

static void	alias_exp_vars(t_command **cmd, bool *changed, t_tool *tool)
{
	while (*cmd && !(*changed))
	{
		perform_alias_exp(*cmd, tool);
		(*changed) = ((*cmd)->purpose != VAR_ASSIGN);
		if ((*cmd)->purpose == VAR_ASSIGN)
			(*cmd) = (*cmd)->next;
	}
}

void	alias_expansion(t_command *cmd, t_tool *tool)
{
	bool	changed;
	char	*old_str;

	while (cmd && cmd->purpose == VAR_ASSIGN)
	{
		perform_alias_exp(cmd, tool);
		cmd = cmd->next;
	}
	changed = false;
	alias_exp_vars(&cmd, &changed, tool);
	if (!cmd)
		return ;
	old_str = ft_strdup(cmd->content);
	while (cmd && old_str && perform_alias_exp(cmd, tool))
	{
		if (!ft_strcmp(old_str, cmd->content))
		{
			free(old_str);
			return ;
		}
		free(old_str);
		old_str = ft_strdup(cmd->content);
	}
	free(old_str);
}
