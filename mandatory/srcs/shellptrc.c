/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellptrc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:40:09 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/29 13:09:29 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

bool	check_rc(int ac, char **av)
{
	av++;
	while (ac > 1)
	{
		if (ft_strcmp(*av, "--norc") == 0
			|| ft_strcmp(*av, "-n") == 0)
			return (0);
		ac--;
		av++;
	}
	return (1);
}

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

static void	execute_rc(int fd_rc, t_tool *tool)
{
	char	*cmd;

	cmd = get_next_line(fd_rc);
	while (cmd)
	{
		cmd_processing(cmd, tool, false);
		cmd = get_next_line(fd_rc);
	}
	close(fd_rc);
}

void	exec_shellptrc(t_tool *tool)
{
	char	*rc_file;
	int		fd_rc;

	rc_file = get_rc_file(tool);
	if (!rc_file)
		return ;
	fd_rc = open(rc_file, O_RDONLY);
	free(rc_file);
	if (fd_rc >= 3)
		execute_rc(fd_rc, tool);
	fd_rc = open("./.shellptrc", O_RDONLY);
	if (fd_rc >= 3)
		execute_rc(fd_rc, tool);
}
