/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mentiel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:34:33 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/06 15:44:54 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"
#include <errno.h>

// TODO & FIX
// pour les messages d'erreurs
// printf ne print pas sur stderr, a la diff de bash
// voir si ca pose prblm
// sinon faut import mon printf qui peut print vers un fd
int	cd_home(t_tool **tool)
{
	char	**home;

	home = env_getval("HOME", (*tool)->env);
	if (!home)
	{
		printf("%s: cd: HOME not set\n", PROG_NAME);
		return (1);
	}
	change_oldpwd(&((*tool)->env));
	if (chdir(home[0]))
	{
		printf("%s: cd: %s: %s\n", PROG_NAME, home[0], strerror(errno));
		return (1);
	}
	change_pwd(home[0], tool);
	return (0);
}

int	simple_cd(char *dest, t_tool **tool)
{
	change_oldpwd(&((*tool)->env));
	if (chdir(dest))
	{
		printf("%s: cd: %s: %s\n", PROG_NAME, dest, strerror(errno));
		return (1);
	}
	change_pwd(dest, tool);
	return (0);
}

int	check_cdpath(char *dest, t_tool **tool)
{
	t_env	*cdpath;
	int		i;
	char	*concat_path;

	cdpath = env_getptr("CDPATH", (*tool)->env);
	if (!cdpath)
		return (1);
	i = -1;
	while (cdpath->value[++i])
	{
		concat_path = concat_multiple(
				(char *[]){cdpath->value[i], "/", dest, NULL });
		if (access(concat_path, R_OK | X_OK) == 0)
		{
			i = simple_cd(concat_path, tool);
			return (free(concat_path), i);
		}
		free(concat_path);
	}
	return (1);
}

int	cd_mentiel(char **cmd, t_tool **tool)
{
	if (cmd[1] && cmd[2])
	{
		printf("%s: cd: too many arguments\n", PROG_NAME);
		return (1);
	}
	if (!cmd[1])
		return (cd_home(tool));
	else if (check_cdpath(cmd[1], tool) == 0)
		return (0);
	return(simple_cd(cmd[1], tool));
}
