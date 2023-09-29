/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_of_styx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 20:36:29 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/29 20:46:43 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	source_of_styx(char **cmd, t_tool *t)
{
	int		fd;
	int		ret;
	char	**save_cenv;

	save_cenv = t->c_env;
	if (!cmd[1])
	{
		printfd(ERR, "%s: filename argument required\n", cmd[0]);
		printfd(ERR, "%s: usage: %s filename\n", cmd[0], cmd[0]);
		return (2);
	}
	fd = open(cmd[1], O_RDONLY);
	if (fd < 3)
	{
		printfd(ERR, "%s: No such file or directory\n", cmd[1]);
		return (1);
	}
	ret = execute_rc(fd, t);
	t->c_env = save_cenv;
	return (ret);
}
