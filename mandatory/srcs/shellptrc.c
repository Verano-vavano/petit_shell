/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellptrc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:40:09 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/25 10:57:02 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	*get_rc_file(t_tool *tool)
{
	char	*home;
	char	*rc;

	home = get_home(tool->env);
	if (!home)
		return (0);
	rc = concat_multiple((char *[]){home, "/", RC, NULL});
	free(home);
	return (rc);
}

void	exec_shellptrc(t_tool *tool)
{
	char	*cmd;
	char	*rc_file;
	int		fd_rc;

	rc_file = get_rc_file(tool);
	if (!rc_file)
		return ;
	fd_rc = open(rc_file, O_RDONLY);
	free(rc_file);
	if (fd_rc < 3)
		return ;
	cmd = get_next_line(fd_rc);
	while (cmd)
	{
		cmd_processing(cmd, tool, false);
		cmd = get_next_line(fd_rc);
	}
	close(fd_rc);
}
