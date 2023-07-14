/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_comprehension.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:00:40 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/14 13:54:27 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static enum e_cmd_part	redir_post(t_command *cmd, char *s)
{
	enum e_cmd_part	redir;

	redir = redirection_check(cmd, s);
	if (redir == ERROR)
		return (ERROR);
	else if (redir > 1)
		return (redir);
	else if (redir == 0 && !is_metachar(s[0]))
		cmd->purpose = COMMAND;
	return (UNDEFINED);
}

static enum e_cmd_part	get_purpose(t_command *cmd, enum e_cmd_part purpose)
{
	char	*s;

	s = cmd->content;
	if (purpose >= IN_FILE && purpose <= OUT_FILE_APP && s[0] == '&')
	{
		cmd->purpose = REDIR_ID;
		return (purpose);
	}
	else if (purpose != UNDEFINED)
	{
		cmd->purpose = purpose;
		return (UNDEFINED);
	}
	if (is_cmd_delim(s))
		cmd->purpose = CMD_DELIM;
	else if (is_metachar(s[0]))
		cmd->purpose = DELIM;
	return (redir_post(cmd, s));
}

int	understand_the_line(t_command *cmd)
{
	t_command		*cmd_cpy;
	enum e_cmd_part	next_purpose;

	cmd_cpy = cmd;
	next_purpose = UNDEFINED;
	while (cmd_cpy->next)
	{
		next_purpose = get_purpose(cmd_cpy, next_purpose);
		if (next_purpose == ERROR)
		{
			free_command(cmd);
			return (1);
		}
		cmd_cpy = cmd_cpy->next;
	}
	get_purpose(cmd_cpy, next_purpose);
	return (0);
}
