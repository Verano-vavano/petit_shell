/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_satanism_tests.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:03:56 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/12 14:11:39 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	perform_arith_tests(char *op, long arg1, long arg2)
{
	if (!ft_strcmp(op, "-eq"))
		return (arg1 != arg2);
	else if (!ft_strcmp(op, "-ne"))
		return (arg1 == arg2);
	else if (!ft_strcmp(op, "-lt"))
		return (arg1 >= arg2);
	else if (!ft_strcmp(op, "-le"))
		return (arg1 > arg2);
	else if (!ft_strcmp(op, "-gt"))
		return (arg1 <= arg2);
	else if (!ft_strcmp(op, "-ge"))
		return (arg1 < arg2);
	return (2);
}

static int	double_expr_arit_test(char **cmd, char *cmd_name)
{
	long	arg1;
	long	arg2;

	if (!ft_strcmp(cmd[1], "-eq") || !ft_strcmp(cmd[1], "-ne")
		|| !ft_strcmp(cmd[1], "-lt") || !ft_strcmp(cmd[1], "-le")
		|| !ft_strcmp(cmd[1], "-gt") || !ft_strcmp(cmd[1], "-ge"))
	{
		if (!is_long(cmd[0], true))
			return (2 + 0 * printfd(ERR,
					"%s: %s: integer expression expected\n", cmd_name, cmd[0]));
		else if (!is_long(cmd[2], true))
			return (2 + 0 * printfd(ERR,
					"%s: %s: integer expression expected\n", cmd_name, cmd[2]));
		else
		{
			arg1 = ft_atol(cmd[0]);
			arg2 = ft_atol(cmd[2]);
		}
	}
	else
		return (2 + 0 * printfd(ERR,
				"%s: %s: binary operator expected\n", cmd_name, *cmd));
	return (perform_arith_tests(cmd[1], arg1, arg2));
}

int	double_expr_test(char **cmd, char *cmd_name)
{
	if (!ft_strcmp(cmd[1], "=") || !ft_strcmp(cmd[1], "=="))
		return (ft_strcmp(cmd[0], cmd[2]) != 0);
	else if (!ft_strcmp(cmd[1], "!="))
		return (ft_strcmp(cmd[0], cmd[2]) == 0);
	else if (!ft_strcmp(cmd[1], ">"))
		return (ft_strcmp(cmd[0], cmd[2]) < 0);
	else if (!ft_strcmp(cmd[1], "<"))
		return (ft_strcmp(cmd[0], cmd[2]) > 0);
	else if (!ft_strcmp(cmd[1], "-ef"))
		return (!files_ef(cmd[0], cmd[2]));
	else if (!ft_strcmp(cmd[1], "-nt"))
		return (!files_nt(cmd[0], cmd[2]));
	else if (!ft_strcmp(cmd[1], "-ot"))
		return (!files_ot(cmd[0], cmd[2]));
	else
		return (double_expr_arit_test(cmd, cmd_name));
}

static int	more_unary_tests(char *op, char *arg, char *cmd_name)
{
	if (!ft_strcmp(op, "-p"))
		return (!is_fifo(arg));
	else if (!ft_strcmp(op, "-r"))
		return (access(arg, R_OK) != 0);
	else if (!ft_strcmp(op, "-S"))
		return (!is_sock(arg));
	else if (!ft_strcmp(op, "-s"))
		return (!is_empty_file(arg));
	else if (!ft_strcmp(op, "-t"))
		return (!(is_long(arg, true) && isatty(ft_atol(arg)) == 1));
	else if (!ft_strcmp(op, "-u"))
		return (!is_uid(arg));
	else if (!ft_strcmp(op, "-w"))
		return (access(arg, W_OK) != 0);
	else if (!ft_strcmp(op, "-x"))
		return (access(arg, X_OK) != 0);
	else if (!ft_strcmp(op, "-z"))
		return (ft_strlen(arg) != 0);
	printfd(ERR, "%s: %s: unary operator expected\n", cmd_name, op);
	return (2);
}

int	single_expr_test(char **cmd, char *cmd_name)
{
	if (!ft_strcmp(*cmd, "-a") || !ft_strcmp(*cmd, "-e"))
		return (access(cmd[1], F_OK) != 0);
	else if (!ft_strcmp(*cmd, "-b"))
		return (!is_blk(cmd[1]));
	else if (!ft_strcmp(*cmd, "-c"))
		return (!is_chr(cmd[1]));
	else if (!ft_strcmp(*cmd, "-d"))
		return (!is_dir(cmd[1]));
	else if (!ft_strcmp(*cmd, "-f"))
		return (!is_reg(cmd[1]));
	else if (!ft_strcmp(*cmd, "-g"))
		return (!is_gid(cmd[1]));
	else if (!ft_strcmp(*cmd, "-h") || !ft_strcmp(*cmd, "-L"))
		return (!is_lnk(cmd[1]));
	else if (!ft_strcmp(*cmd, "-n"))
		return (ft_strlen(cmd[1]) == 0);
	return (more_unary_tests(*cmd, cmd[1], cmd_name));
}
