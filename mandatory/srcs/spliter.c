/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:43:04 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/04 15:02:51 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	not_ended(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (len >= 1 && (s[len - 1] == '|' || s[len - 1] == '\\'
			|| s[len - 1] == '\'' || s[len - 1] == '"'))
		return (1);
	else if (len >= 2 && !ft_strcmp(s + (len - 2), "&&"))
		return (1);
	return (0);
}

static char	*new_line_add(char *line, t_command *cmd_cpy)
{
	char	*new_line;
	char	*joined;

	new_line = 0;
	while (!new_line || !(*new_line))
		new_line = readline("> ");
	joined = ft_strjoin(line, " ");
	free(line);
	ft_split_cmd(new_line, cmd_cpy);
	line = ft_strjoin(joined, new_line);
	free(new_line);
	free(joined);
	return (line);
}

t_command	*spliter_init(char *line)
{
	t_command		*cmd;
	t_command		*cmd_cpy;

	cmd = 0;
	cmd_cpy = cmd;
	while (1)
	{
		while (cmd_cpy && cmd_cpy->next)
			cmd_cpy = cmd_cpy->next;
		if (cmd_cpy && !not_ended(cmd_cpy->content))
			break ;
		if (cmd_cpy)
			line = new_line_add(line, cmd_cpy);
		else
		{
			cmd = ft_split_cmd(line, cmd_cpy);
			cmd_cpy = cmd;
		}
	}
	add_history(line);
	return (cmd);
}
