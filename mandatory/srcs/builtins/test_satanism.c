/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_satanism.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:53:43 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/12 14:29:49 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	try_more(char **cmd, char *cmd_name, int in_par);

static int	get_test_result(char ***cmd, char *cmd_name)
{
	int	narg;
	int	ret;

	narg = 0;
	narg = test_three(*cmd);
	if (!narg)
		narg = test_two(*cmd);
	if (!narg)
		narg = 1;
	ret = search_and_perform_test(*cmd, cmd_name, narg);
	(*cmd) += narg;
	return (ret);
}

static int	try_loop(char **cmd, char *cmd_name, int in_par, int ret)
{
	if (!ft_strcmp(*cmd, "-a") || !ft_strcmp(*cmd, "-o"))
	{
		if (cmd[0][1] == 'a' && ret == 0)
			return (try_more(cmd + 1, cmd_name, in_par));
		else if (cmd[0][1] == 'o' && ret == 1)
			return (try_more(cmd + 1, cmd_name, in_par));
		cmd = go_to_end(cmd, cmd_name, &in_par);
		if (!cmd)
			return (2);
		if (!(*cmd) || (cmd_name[0] == '[' && !cmd[1]))
			return (ret);
		if (cmd[0][1] == 'a' && ret == 0)
			return (try_more(cmd + 1, cmd_name, in_par));
		else if (cmd[0][1] == 'o' && ret == 1)
			return (try_more(cmd + 1, cmd_name, in_par));
		else if (cmd[0][1] == 'a' || cmd[0][1] == 'o')
			return (ret);
	}
	else if (cmd[0][0] == '-')
		printfd(ERR, "%s: syntax error: `%s' unexpected\n", cmd_name, cmd[0]);
	else
		printfd(ERR, "%s: too many arguments\n", cmd_name);
	return (2);
}

int	try_more(char **cmd, char *cmd_name, int in_par)
{
	bool	neg;
	int		ret;

	neg = false;
	while (*cmd && ft_strcmp(*cmd, "!") == 0)
	{
		neg ^= 1;
		cmd++;
	}
	if (*cmd && ft_strcmp(*cmd, "(") == 0)
		return (try_more(cmd + 1, cmd_name, in_par + 1) ^ neg);
	ret = (get_test_result(&cmd, cmd_name) ^ neg);
	while (cmd && *cmd && in_par && !ft_strcmp(*cmd, ")"))
	{
		in_par--;
		cmd++;
	}
	if (!cmd || !(*cmd))
		return (ret);
	return (try_loop(cmd, cmd_name, in_par, ret));
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
	ret = try_more(cmd + 1, cmd[0], 0);
	if (ret == 2 || ret == 3)
		return (2);
	return (ret);
}
