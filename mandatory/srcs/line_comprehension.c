/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_comprehension.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:00:40 by hdupire           #+#    #+#             */
/*   Updated: 2023/06/30 11:16:39 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static enum e_cmd_part	get_purpose(t_command *cmd, enum e_cmd_part purpose)
{
	char	*s;
	int		redir;

	s = cmd->content;
	purpose = IN_FILE;
	if (meta_check(cmd))
		return (ERROR);
	if (purpose >= IN_FILE && (s[0] == '<' || s[0] == '>'))
	{
		syntax_error(s);
		return (ERROR);
	}
	redir = redirection_check(cmd, s);
	if (redir == ERROR)
		return (ERROR);
	else if (redir > 1)
		return (redir);
	/*else if (redir == 0)
		cmd = sub_command_check(cmd, s);*/
	return (UNDEFINED);
}

void	understand_the_line(char *line)
{
	t_command		*cmd;
	t_command		*cmd_cpy;
	enum e_cmd_part	next_purpose;

	cmd = ft_split_cmd(line);
	cmd_cpy = cmd;
	next_purpose = UNDEFINED;
	while (cmd_cpy->next)
	{
		next_purpose = get_purpose(cmd_cpy, next_purpose);
		if (next_purpose == ERROR)
		{
			free_linked_list(cmd);
			free(line);
			line = 0;
			return ;
		}
		printf("lol");
		cmd_cpy = cmd_cpy->next;
	}
	get_purpose(cmd_cpy, next_purpose);
}
