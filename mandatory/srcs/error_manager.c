/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:00:27 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/16 14:03:55 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	syntax_error(char *token, int l)
{
	write(2, "Syntax error near unexpected token `", 36);
	if (l == -1 && token[1] == token[0])
		l = 2;
	else if (l == -1)
		l = 1;
	write(2, token, l);
	write(2, "'\n", 2);
	return (2);
}

int	ambiguous_error(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ambiguous redirect\n", 21);
	return (1);
}

int	some_error(char *cmd, char *error)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (1);
}

int	command_error(char *cmd, int error)
{
	if (error < 125)
		return (error);
	if (error == 125)
		printfd(ERR, "%s: Is a directory\n", cmd);
	else if (error == 126)
		printfd(ERR, "%s: Permission denied\n", cmd);
	else if (error == 127)
		printfd(ERR, "%s: command not found...\n", cmd);
	else if (error == 128)
		printfd(ERR, "%s: No such file or directory\n", cmd);
	if (error <= 126)
		return (126);
	return (127);
}
