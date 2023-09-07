/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mentiel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:34:33 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/07 10:49:20 by hdupire          ###   ########.fr       */
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
int	cd_home(t_tools **tools)
{
	char	**home;

	home = env_getval("HOME", (*tools)->env);
	if (!home)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	change_oldpwd(&((*tools)->env));
	if (chdir(home[0]))
	{
		write(2, "cd: ", 4);
		perror(home[0]);
		return (1);
	}
	change_pwd(home[0], tools);
	return (0);
}

int	simple_cd(char *dest, t_tools **tools)
{
	if (access(dest, R_OK | X_OK) != 0)
	{
		write(2, "cd: ", 4);
		perror(dest);
		return (1);
	}
	change_oldpwd(&((*tools)->env));
	if (chdir(dest))
	{
		write(2, "cd: ", 4);
		perror(dest);
		return (1);
	}
	change_pwd(dest, tools);
	return (0);
}

int	check_cdpath(char *dest, t_tools **tools)
{
	t_env	*cdpath;
	int		i;
	int		ret;
	char	*concat_path;

	cdpath = env_getptr("CDPATH", (*tools)->env);
	if (!cdpath)
		return (1);
	i = -1;
	while (cdpath->value[++i])
	{
		concat_path = concat_multiple(
				(char *[]){cdpath->value[i], "/", dest, NULL });
		if (access(concat_path, R_OK | X_OK) == 0)
		{
			ret = simple_cd(concat_path, tools);
			free(concat_path);
			return (ret);
		}
		free(concat_path);
	}
	return (1);
}

int	cd_mentiel(char **cmd, t_tools **tools)
{
	if (cmd[1] && cmd[2])
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	if (!cmd[1])
		return (cd_home(tools));
	else if (check_cdpath(cmd[1], tools) == 0)
		return (0);
	return (simple_cd(cmd[1], tools));
}
