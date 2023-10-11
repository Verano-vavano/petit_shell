/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_satanism.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:53:43 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/11 19:29:24 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

/*
static int	double_expr_test(char **cmd, char *cmd_name)
{
	if (!ft_strcmp(cmd[1], "="))
		return (ft_strcmp(cmd[0], cmd[2]) != 0);
	printfd(ERR, "%s: %s: unary operator expected\n", cmd_name, *cmd);
	return (2);
}*/

static int	single_expr_test(char **cmd, char *cmd_name)
{
	if (!ft_strcmp(*cmd, "-z"))
		return (ft_strlen(cmd[1]) != 0);
	else if (!ft_strcmp(*cmd, "-n"))
		return (ft_strlen(cmd[1]) == 0);
	else if (!ft_strcmp(*cmd, "-e"))
		return (access(cmd[1], F_OK) != 0);
	else if (!ft_strcmp(*cmd, "-f"))
		return (!is_reg(cmd[1]));
	else if (!ft_strcmp(*cmd, "-d"))
		return (!is_dir(cmd[1]));
	else if (!ft_strcmp(*cmd, "-h") || !ft_strcmp(*cmd, "-L"))
		return (!is_lnk(cmd[1]));
	else if (!ft_strcmp(*cmd, "-b"))
		return (!is_blk(cmd[1]));
	else if (!ft_strcmp(*cmd, "-c"))
		return (!is_chr(cmd[1]));
	else if (!ft_strcmp(*cmd, "-p"))
		return (!is_fifo(cmd[1]));
	else if (!ft_strcmp(*cmd, "-S"))
		return (!is_sock(cmd[1]));
	else if (!ft_strcmp(*cmd, "-s"))
		return (!is_empty_file(cmd[1]));
	else if (!ft_strcmp(*cmd, "-t"))
		return (!(is_long(cmd[1], true) && isatty(ft_atol(cmd[1])) == 1));
	else if (!ft_strcmp(*cmd, "-r"))
		return (access(cmd[1], R_OK) != 0);
	else if (!ft_strcmp(*cmd, "-w"))
		return (access(cmd[1], W_OK) != 0);
	else if (!ft_strcmp(*cmd, "-x"))
		return (access(cmd[1], X_OK) != 0);
	else if (!ft_strcmp(*cmd, "-g"))
		return (!is_gid(cmd[1]));
	else if (!ft_strcmp(*cmd, "-u"))
		return (!is_uid(cmd[1]));
	printfd(ERR, "%s: %s: unary operator expected\n", cmd_name, *cmd);
	return (2);
}

static int	search_and_perform_test(char **cmd, char *cmd_name, int narg)
{
	bool	neg;

	neg = false;
	if (ft_strcmp(*cmd, "!") == 0)
	{
		neg = true;
		narg--;
		cmd++;
	}
	if (narg == 0)
		return (1 ^ neg);
	else if (narg == 1)
		return ((**cmd == 0) ^ neg);
	else if (narg == 2)
		return ((single_expr_test(cmd, cmd_name)) ^ neg);
	return (0 ^ neg);
}

int	test_satanism(char **cmd)
{
	int	ret;
	int	narg;

	signal(SIGINT, SIG_DFL);
	narg = 1;
	while (cmd[narg])
		narg++;
	narg--;
	if (cmd[0][0] == '[')
	{
		if (ft_strcmp(cmd[narg], "]"))
		{
			printfd(ERR, "[: missing `]'\n");
			return (2);
		}
		cmd[narg] = 0;
		narg--;
	}
	ret = search_and_perform_test(cmd + 1, cmd[0], narg);
	return (ret);
}
