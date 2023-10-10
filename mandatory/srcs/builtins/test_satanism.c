/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_satanism.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:53:43 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/10 23:01:09 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	double_expr_test(char **cmd, char *cmd_name)
{
	if (!ft_strcmp(cmd[1], "="))
		return (ft_strcmp(cmd[0], cmd[2]) != 0);
	printfd(ERR, "%s: %s: unary operator expected\n", cmd_name, *cmd);
	return (2);
}

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

static int	get_operator_type(char **cmd, int start, bool brack)
{
	int	i;

	i = 0;
	while (cmd && cmd[i + start])
	{
		if (!cmd[i + start + 1] && brack && ft_strcmp("]", cmd[i + start]))
		{
			printfd(ERR, "%s: missing `]'\n", cmd[0]);
			return (-2);
		}
		i++;
	}
	i -= (1 + brack);
	if (i + brack < 0)
		return (-1);
	else if (i + brack == 0)
		return (0);
	else if (i + brack > 2)
	{
		printfd(ERR, "%s: too many arguments\n", cmd[0]);
		return (-2);
	}
	return (i);
}

int	test_satanism(char **cmd)
{
	int		ret;
	bool	negate;
	bool	brack;
	int		operator_type;
	int		start;

	ret = 0;
	brack = (cmd[0][0] == '[');
	start = 1;
	negate = false;
	if (ft_strcmp(cmd[start], "!") == 0)
	{
		start++;
		negate = true;
	}
	operator_type = get_operator_type(cmd, start, brack);
	if (operator_type < 0)
		return (operator_type * (-1));
	if (operator_type == 1)
		ret = single_expr_test(cmd + start, cmd[0]);
	else if (operator_type == 2)
		ret = double_expr_test(cmd + start, cmd[0]);
	if (negate && ret != 2)
		return (!ret);
	return (ret);
}
