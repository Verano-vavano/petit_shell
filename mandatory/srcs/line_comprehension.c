/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_comprehension.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:00:40 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/04 11:22:45 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static enum e_cmd_part	get_purpose(t_command *cmd, enum e_cmd_part purpose)
{
	char	*s;
	int		redir;

	if (purpose != UNDEFINED)
	{
		cmd->purpose = purpose;
		return (UNDEFINED);
	}
	s = cmd->content;
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
	else if (redir == 0 && !is_metachar(s[0]))
		cmd->purpose = COMMAND;
	return (UNDEFINED);
}

static int	not_ended(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (len >= 1 && (s[len - 1] == '|' || s[len - 1] == '\\'))
		return (1);
	else if (len >= 2 && !ft_strcmp(s + (len - 2), "&&"))
		return (1);
	return (0);
}

t_command	*understand_the_line(char *line)
{
	t_command		*cmd;
	t_command		*cmd_cpy;
	char			*new_line;
	char			*joined;
	enum e_cmd_part	next_purpose;

	cmd = 0;
	cmd_cpy = cmd;
	while (1)
	{
		while (cmd_cpy && cmd_cpy->next)
			cmd_cpy = cmd_cpy->next;
		if (cmd_cpy && !not_ended(cmd_cpy->content))
			break ;
		if (cmd_cpy)
		{
			new_line = 0;
			while (!new_line || !(*new_line))
				new_line = readline("> ");
			joined = ft_strjoin(line, " ");
			free(line);
			ft_split_cmd(new_line, cmd_cpy);
			line = ft_strjoin(joined, new_line);
			free(new_line);
			free(joined);
		}
		else
		{
			cmd = ft_split_cmd(line, cmd_cpy);
			cmd_cpy = cmd;
		}
	}
	cmd_cpy = cmd;
	next_purpose = UNDEFINED;
	while (cmd_cpy->next)
	{
		next_purpose = get_purpose(cmd_cpy, next_purpose);
		if (next_purpose == ERROR)
		{
			free_linked_list(cmd);
			line = 0;
			return (0);
		}
		printf("%s %d\n", cmd_cpy->content, cmd_cpy->purpose);
		cmd_cpy = cmd_cpy->next;
	}
	get_purpose(cmd_cpy, next_purpose);
	printf("%s %d\n", cmd_cpy->content, cmd_cpy->purpose);
	add_history(line);
	free(line);
	return (cmd);
}
