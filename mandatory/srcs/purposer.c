/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:56:48 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/10 17:57:00 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	check_redir_type(char way, int purp, t_command *cmd, char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (len == 3 && s[0] == s[1] && s[0] == s[2])
	{
		cmd->purpose = REDIR_ID;
		return (HERE_STRING);
	}
	else if (len == 2 && s[1] == way)
	{
		cmd->purpose = REDIR_ID;
		return (purp + 2);
	}
	else if (len == 1)
	{
		cmd->purpose = REDIR_ID;
		return (purp);
	}
	return (UNDEFINED);
}

int	redirection_check(t_command *cmd, char *s)
{
	int		i;

	i = 0;
	if (s[i] == '&')
		i++;
	while (s[i] && s[i] != '<' && s[i] != '>' && is_num(s[i]))
		i++;
	if (s[i] == '<' && s[i + 1] == '>')
	{
		cmd->purpose = REDIR_ID;
		return (IN_OUT_FILE);
	}
	if (s[i] == '<')
		return (check_redir_type('<', IN_FILE, cmd, s + i));
	else if (s[i] == '>')
		return (check_redir_type('>', OUT_FILE, cmd, s + i));
	return (UNDEFINED);
}
