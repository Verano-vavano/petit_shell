/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:31:39 by hdupire           #+#    #+#             */
/*   Updated: 2023/06/30 19:02:59 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
/*
void	get_text(t_piping *p, int *pipe)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		line[ft_strchr_int(line, '\n')] = 0;
		if (!(ft_strcmp(line, p->limit)))
			break ;
		line[ft_strchr_int(line, '\n')] = '\n';
		write(*pipe, line, ft_strlen(line));
		free(line);
	}
	free(line);
}*/

int	here_doc(t_command *cmd)
{
	t_command	*cmd_cpy;

	cmd_cpy = cmd;

	return (0);
}
