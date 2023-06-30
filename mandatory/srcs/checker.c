/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:56:48 by hdupire           #+#    #+#             */
/*   Updated: 2023/06/30 18:36:30 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	check_redir_type(char way, int purp1, int purp2, t_command *cmd)
{
	size_t	len;
	char	*s;

	s = cmd->content;
	len = ft_strlen(s);
	if (len == 2 && s[1] == way)
	{
		cmd->purpose = DELIM;
		return (purp2);
	}
	else if (len == 1)
	{
		cmd->purpose = DELIM;
		return (purp1);
	}
	return (UNDEFINED);
}

int	redirection_check(t_command *cmd, char *s)
{
	size_t	len;
	char	c;

	len = ft_strlen(s);
	if (len > 1
		&& ((s[0] == '<' && s[1] == '>') || (s[0] == '>' && s[1] == '<')))
	{
		syntax_error(s + 1);
		return (ERROR);
	}
	else if (cmd->next && is_metachar(cmd->next->content[0]))
	{
		c = cmd->next->content[0];
		syntax_error(&c);
		return (ERROR);
	}
	if (s[0] == '<')
		return (check_redir_type('<', IN_FILE, HERE_DOC_DELIM, cmd));
	else if (s[0] == '>')
		return (check_redir_type('>', OUT_FILE, OUT_FILE_APP, cmd));
	return (UNDEFINED);
}

int	meta_check(t_command *cmd)
{
	size_t	len;
	char	*s;

	len = ft_strlen(cmd->content);
	s = cmd->content;
	if (is_metachar(s[0]))
		cmd->purpose = DELIM;
	if (len == 1 && is_metachar(s[0])
		&& cmd->next && is_strict_meta(cmd->next->content[0]))
		syntax_error(cmd->next->content);
	else if (len > 1 && s[0] == ';' && s[1] == ';')
		syntax_error(";;");
	else if (len > 1 && is_metachar(s[0]) && is_metachar(s[1]) && s[1] != s[0])
		syntax_error(s + 1);
	else if (len > 2
		&& is_metachar(s[0]) && is_metachar(s[1]) && is_metachar(s[2]))
		syntax_error(s + 2);
	else
		return (0);
	return (1);
}
