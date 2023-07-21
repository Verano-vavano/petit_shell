/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:00:27 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/21 07:37:37 by hdupire          ###   ########.fr       */
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
	return (1);
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
	char	*temp;
	char	*temp2;

	if (error != 126 && error != 127)
		return (error);
	temp = ft_strjoin(cmd, ": ");
	if (!temp)
		return (error);
	if (error == 126)
		temp2 = ft_strjoin(temp, "Permission denied\n");
	else if (error == 127)
		temp2 = ft_strjoin(temp, "command not found...\n");
	free(temp);
	if (!temp2)
		return (error);
	write(2, temp2, ft_strlen(temp2));
	free(temp2);
	return (error);
}
