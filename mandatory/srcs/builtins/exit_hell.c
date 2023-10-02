/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:15:30 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/02 13:54:02 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static long	get_exit_code(char **cmd, long ret)
{
	if (cmd && cmd[1])
	{
		if (!is_long(cmd[1], true))
		{
			printfd(ERR, "exit: %s: numeric argument required\n", cmd[1]);
			return (2);
		}
		else
			return (ft_atol(cmd[1]));
	}
	else
		return (ret);
}

int	exit_hell(char **cmd, long ret, t_tool *tool, bool one)
{
	long	exit_code;

	if (cmd && cmd[1] && cmd[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return (1);
	}
	exit_code = get_exit_code(cmd, ret);
	if (one && tool->c_env)
		free_char_etoile_etoile(tool->c_env);
	if (one && tool->cwd)
		free(tool->cwd);
	free_whole_env(tool->env);
	free_alias(tool->alias_start);
	exit(exit_code % 256);
}
