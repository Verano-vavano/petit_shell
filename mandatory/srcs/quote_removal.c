/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:10:43 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/21 07:19:15 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

char	*quote_removal(char *cmd)
{
	int		i;
	bool	backslashed;
	char	quoted;
	char	new_quoted;
	char	*temp;

	i = 0;
	quoted = 0;
	backslashed = false;
	while (cmd[i])
	{
		temp = 0;
		new_quoted = is_quoted(cmd, i, quoted);
		if (quoted == 0 && i > 0 && cmd[i - 1] == '\\' && !backslashed)
		{
			temp = ft_strreplace(cmd, i - 1, 1, "\0");
			backslashed = true;
			i--;
		}
		else if (quoted == '"' && i > 0 && cmd[i - 1] == '\\' && !backslashed
			&& (cmd[i] == '\\' || cmd[i] == '"' || cmd[i] == '$'))
		{
			temp = ft_strreplace(cmd, i - 1, 1, "\0");
			backslashed = true;
			i--;
		}
		else if (quoted != new_quoted)
		{
			backslashed = false;
			temp = ft_strreplace(cmd, i, 1, "\0");
			i--;
		}
		else
			backslashed = false;
		quoted = new_quoted;
		if (temp)
		{
			free(cmd);
			cmd = temp;
		}
		i++;
	}
	return (cmd);
}

void	quote_remove_cmd(t_command *cmd)
{
	while (cmd)
	{
		cmd->content = quote_removal(cmd->content);
		printf("%s\n", cmd->content);
		cmd = cmd->next;
	}
}
