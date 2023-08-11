/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mentiel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:34:33 by tcharanc          #+#    #+#             */
/*   Updated: 2023/08/10 22:10:51 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>


// TODO & FIX
// pour les messages d'erreurs
// printf ne print pas sur stderr, a la diff de bash
// voir si ca pose prblm
// sinon faut import mon printf qui peut print vers un fd
int	cd_home(t_env *env)
{
	char **home;

	home = env_getval("HOME", env);
	if (!home)
	{
		printf("%s: cd: HOME not set\n",PROG_NAME);
		return (1);
	}
	if (env_contain("OLDPWD", env))
		env_change_val("OLDPWD", getcwd(NULL, 0), env);
	if (chdir(home[0]))
	{
		printf("%s: cd: %s: %s\n", PROG_NAME, home[0], strerror(errno));
		return (1);
	}
	if (env_contain("PWD", env))
		env_change_val("PWD", getcwd(NULL, 0), env);
	return (0);
}

void	simple_cd(char *dest, t_env *env)
{
	if (access(dest, R_OK | X_OK) != 0)
	{
		printf("cc %s: cd: %s: %s\n", PROG_NAME, dest, strerror(errno));
		return ;
	}
	if (env_contain("OLDPWD", env))
		env_change_val("OLDPWD", getcwd(NULL, 0), env);
	if (chdir(dest))
	{
		printf("%s: cd: %s: %s\n", PROG_NAME, dest, strerror(errno));
		return ;
	}
	if (env_contain("PWD", env))
		env_change_val("PWD", getcwd(NULL, 0), env);
}

int	check_cdpath(char *dest, t_env *env)
{
	t_env	*cdpath;
	int		i;
	char	*concat_path;

	cdpath = env_getptr("CDPATH", env);
	if (!cdpath)
		return (1);
	i = -1;
	while(cdpath->value[++i])
	{
		concat_path = concat_multiple(
			(char *[]){ cdpath->value[i] , "/", dest, NULL });
		if (access(concat_path, R_OK | X_OK) == 0)
		{
			simple_cd(concat_path, env);
			return (free(concat_path), 0);
		}
		free(concat_path);
	}
	return (1);
}

int	cd_mentiel(char **cmd, t_env *env)
{
	if (!cmd[1])
		return(cd_home(env));
	else if (check_cdpath(cmd[1], env) == 0)
		return (0);
	simple_cd(cmd[1], env);
	return (0);
}
