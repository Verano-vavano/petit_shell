/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_satanism.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:53:43 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/12 11:34:03 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	search_and_perform_test(char **cmd, char *cmd_name, int narg);

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
	if (!ft_strcmp(cmd[1], "-eq"))
		return (arg1 != arg2);
	else if (!ft_strcmp(cmd[1], "-ne"))
		return (arg1 == arg2);
	else if (!ft_strcmp(cmd[1], "-lt"))
		return (arg1 >= arg2);
	else if (!ft_strcmp(cmd[1], "-le"))
		return (arg1 > arg2);
	else if (!ft_strcmp(cmd[1], "-gt"))
		return (arg1 <= arg2);
	else if (!ft_strcmp(cmd[1], "-ge"))
		return (arg1 < arg2);
	return (2);
}

static int	double_expr_test(char **cmd, char *cmd_name)
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

static int	single_expr_test(char **cmd, char *cmd_name)
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
	else if (!ft_strcmp(*cmd, "-p"))
		return (!is_fifo(cmd[1]));
	else if (!ft_strcmp(*cmd, "-r"))
		return (access(cmd[1], R_OK) != 0);
	else if (!ft_strcmp(*cmd, "-S"))
		return (!is_sock(cmd[1]));
	else if (!ft_strcmp(*cmd, "-s"))
		return (!is_empty_file(cmd[1]));
	else if (!ft_strcmp(*cmd, "-t"))
		return (!(is_long(cmd[1], true) && isatty(ft_atol(cmd[1])) == 1));
	else if (!ft_strcmp(*cmd, "-u"))
		return (!is_uid(cmd[1]));
	else if (!ft_strcmp(*cmd, "-w"))
		return (access(cmd[1], W_OK) != 0);
	else if (!ft_strcmp(*cmd, "-x"))
		return (access(cmd[1], X_OK) != 0);
	else if (!ft_strcmp(*cmd, "-z"))
		return (ft_strlen(cmd[1]) != 0);
	printfd(ERR, "%s: %s: unary operator expected\n", cmd_name, *cmd);
	return (2);
}

static int	test_three(char **cmd)
{
	char	*op;

	if (cmd[0] && cmd[1] && cmd[2])
	{
		op = cmd[1];
		if (!ft_strcmp(op, "=") || !ft_strcmp(op, "==")
			|| !ft_strcmp(op, "!=") || !ft_strcmp(op, ">")
			|| !ft_strcmp(op, "<") || !ft_strcmp(op, "-ef")
			|| !ft_strcmp(op, "-nt") || !ft_strcmp(op, "-ot")
			|| !ft_strcmp(op, "-eq") || !ft_strcmp(op, "-ne")
			|| !ft_strcmp(op, "-lt") || !ft_strcmp(op, "-le")
			|| !ft_strcmp(op, "-gt") || !ft_strcmp(op, "-ge"))
			return (3);
	}
	return (0);
}

static int	test_two(char **cmd)
{
	char	sc;

	if (cmd[0] && cmd[1] && cmd[1][0])
	{
		sc = cmd[0][1];
		if (ft_strlen(cmd[0]) == 2 && cmd[0][0] == '-'
			&& (sc == 'a' || sc == 'b' || sc == 'c' || sc == 'd' || sc == 'e'
				|| sc == 'f' || sc == 'g' || sc == 'h' || sc == 'n' || sc == 'p'
				|| sc == 'r' || sc == 'L' || sc == 'S' || sc == 's' || sc == 't'
				|| sc == 'u' || sc == 'w' || sc == 'x' || sc == 'z'))
			return (2);
	}
	return (0);
}

static char	**go_to_end(char **cmd, char *cmd_name)
{
	while (cmd && *cmd && (cmd_name[0] != '[' || cmd[1] != 0))
		cmd++;
	return (cmd);
}

static int	try_more(char **cmd, char *cmd_name)
{
	bool	neg;
	int		narg;
	int		ret;

	neg = false;
	while (*cmd && ft_strcmp(*cmd, "!") == 0)
	{
		neg ^= 1;
		cmd++;
	}
	narg = 0;
	narg = test_three(cmd);
	if (!narg)
		narg = test_two(cmd);
	if (!narg)
		narg = 1;
	ret = search_and_perform_test(cmd, cmd_name, narg);
	cmd += narg;
	if (!cmd || !(*cmd))
		return (ret ^ neg);
	else if (ft_strcmp(*cmd, "-a") || ft_strcmp(*cmd, "-o"))
	{
		if (cmd[0][1] == 'a' && ret == 0)
			return (try_more(cmd + 1, cmd_name) ^ neg);
		else if (cmd[0][1] == 'o' && ret == 1)
			return (try_more(cmd + 1, cmd_name) ^ neg);
		cmd = go_to_end(cmd, cmd_name);
		if (!cmd || !(*cmd) || (cmd_name[0] == '[' && !cmd[1]))
			return (ret ^ neg);
	}
	else if (cmd[0][0] == '-')
		printfd(ERR, "%s: syntax error: `%s' unexpected\n", cmd_name, cmd[0]);
	else
		printfd(ERR, "%s: too many arguments\n", cmd_name);
	return (2);
}

int	search_and_perform_test(char **cmd, char *cmd_name, int narg)
{
	bool	neg;

	neg = false;
	while (*cmd && ft_strcmp(*cmd, "!") == 0)
	{
		neg ^= 1;
		narg--;
		cmd++;
	}
	if (narg == 0)
		return (1 ^ neg);
	else if (narg == 1)
		return ((*cmd == 0 || **cmd == 0) ^ neg);
	else if (narg == 2)
		return ((single_expr_test(cmd, cmd_name)) ^ neg);
	else if (narg == 3)
		return ((double_expr_test(cmd, cmd_name)) ^ neg);
	else
		return (try_more(cmd, cmd_name) ^ neg);
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
	ret = try_more(cmd + 1, cmd[0]);
	if (ret == 2 || ret == 3)
		return (2);
	return (ret);
}
