/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:31:36 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/29 21:32:43 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

// Gotta love not using switch cases (i hate it)
char	*replace_escaped(char *cmd, int i)
{
	if (cmd[i + 1] == '\\')
		return (ft_strreplace(cmd, i, 2, "\\"));
	else if (cmd[i + 1] == '"')
		return (ft_strreplace(cmd, i, 2, "\""));
	else if (cmd[i + 1] == '\'')
		return (ft_strreplace(cmd, i, 2, "'"));
	else if (cmd[i + 1] == 'n')
		return (ft_strreplace(cmd, i, 2, "\n"));
	else if (cmd[i + 1] == 't')
		return (ft_strreplace(cmd, i, 2, "\t"));
	else if (cmd[i + 1] == 'r')
		return (ft_strreplace(cmd, i, 2, "\r"));
	else if (cmd[i + 1] == 'b')
		return (ft_strreplace(cmd, i, 2, "\b"));
	else if (cmd[i + 1] == 'a')
		return (ft_strreplace(cmd, i, 2, "\a"));
	else if (cmd[i + 1] == 'f')
		return (ft_strreplace(cmd, i, 2, "\f"));
	else if (cmd[i + 1] == 'v')
		return (ft_strreplace(cmd, i, 2, "\v"));
	else if (cmd[i + 1] == 'e')
		return (ft_strreplace(cmd, i, 2, "\e"));
	else if (cmd[i + 1] == '0')
		return (ft_strreplace(cmd, i, 2, "\0"));
	return (0);
}
