/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_satanism_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:16:18 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/12 14:18:43 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	test_three(char **cmd)
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

int	test_two(char **cmd)
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

char	**go_to_end(char **cmd, char *cmd_name, int *in_par)
{
	while (cmd && *cmd && (cmd_name[0] != '[' || cmd[1] != 0))
	{
		if (*in_par && ft_strcmp(*cmd, ")") == 0)
		{
			(*in_par)--;
			return (cmd + 1);
		}
		cmd++;
	}
	if (*in_par)
	{
		printfd(ERR, "%s: `)' expected", cmd_name);
		if (cmd_name[0] == '[')
			printfd(ERR, ", found ]\n");
		else
			printfd(ERR, "\n");
		return (0);
	}
	return (cmd);
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
	return (0 ^ neg);
}
