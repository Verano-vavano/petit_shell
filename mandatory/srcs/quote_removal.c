/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:10:43 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/02 16:23:44 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	*last_rm_checks(char *cmd, char *quoted, int *i_bkd, int i)
{
	if (!quoted[0] && cmd[i] == '\\' && !i_bkd[1])
	{
		i_bkd[1] = true;
		i_bkd[0]--;
		return (ft_strreplace(cmd, i, 1, "\0"));
	}
	if (quoted[0] != quoted[1] && (quoted[0] != CQUOTES || quoted[1] != '\''))
	{
		i_bkd[0] -= 1 + (quoted[1] == CQUOTES);
		i_bkd[1] = false;
		if (quoted[1] == CQUOTES)
			return (ft_strreplace(cmd, i - 1, 2, "\0"));
		return (ft_strreplace(cmd, i, 1, "\0"));
	}
	i_bkd[1] = false;
	return (0);
}

static char	*quote_rm_check(char *quoted, int *i_bkd, char *cmd)
{
	int		i;
	bool	backslashed;
	char	*temp;

	i = i_bkd[0];
	backslashed = i_bkd[1];
	if (quoted[0] == CQUOTES && i > 0 && cmd[i - 1] == '\\')
	{
		i_bkd[0]--;
		temp = replace_escaped(cmd, i - 1);
		if (temp)
			return (temp);
	}
	if (quoted[0] != '\'' && i > 0 && cmd[i - 1] == '\\' && !backslashed
		&& (cmd[i] == '\\' || cmd[i] == '"' || cmd[i] == '$'))
	{
		i_bkd[0]--;
		i_bkd[1] = true;
		return (ft_strreplace(cmd, i - 1, 1, "\0"));
	}
	return (last_rm_checks(cmd, quoted, i_bkd, i));
}

char	*quote_removal(char *cmd)
{
	int		i_bkd[2];
	char	quoted[2];
	char	*temp;
	bool	dollar;

	i_bkd[0] = -1;
	i_bkd[1] = false;
	quoted[0] = NOQUOTES;
	dollar = 0;
	while (cmd && cmd[++i_bkd[0]])
	{
		temp = 0;
		quoted[1] = is_quoted(cmd, i_bkd[0], quoted[0]);
		if (quoted[1] == '\'' && dollar)
			quoted[1] = CQUOTES;
		temp = quote_rm_check(quoted, i_bkd, cmd);
		quoted[0] = quoted[1];
		if (temp && temp != cmd)
		{
			free(cmd);
			cmd = temp;
		}
		dollar = (i_bkd[0] >= 0 && !(quoted[0]) && cmd[i_bkd[0]] == '$');
	}
	return (cmd);
}

void	quote_remove_cmd(t_command *cmd)
{
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		cmd->content = quote_removal(cmd->content);
		cmd = cmd->next;
	}
}
