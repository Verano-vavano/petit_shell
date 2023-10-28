/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mentiel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:34:33 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/28 21:21:17 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"
#include <errno.h>

int	cd_home(t_tool **tool)
{
	char	*home;

	home = env_getval("HOME", (*tool)->env);
	if (!home)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	change_oldpwd(&((*tool)->env));
	if (chdir(home))
	{
		write(2, "cd: ", 4);
		perror(home);
		return (1);
	}
	change_pwd(home, tool);
	return (0);
}

int	simple_cd(char *dest, t_tool **tool, bool free_it)
{
	printf("%s\n", dest);
	if (access(dest, R_OK | X_OK) != 0)
	{
		write(2, "cd: ", 4);
		perror(dest);
		if (free_it)
			free(dest);
		return (1);
	}
	change_oldpwd(&((*tool)->env));
	if (chdir(dest))
	{
		write(2, "cd: ", 4);
		perror(dest);
		if (free_it)
			free(dest);
		return (1);
	}
	change_pwd(dest, tool);
	if (free_it)
		free(dest);
	return (0);
}

static bool	check_moving(char *dest)
{
	if (dest[0] == '.')
	{
		if ((!dest[1] || dest[1] == '/'))
			return (false);
		else if (dest[1] == '.'
			&& (!dest[2] || dest[2] == '/'))
			return (false);
	}
	return (true);
}

int	check_cdpath(char *dest, t_tool **tool)
{
	char	**cdpath;
	int		i;
	int		ret;
	char	*concat_path;
	bool	shmoving;

	cdpath = env_getval_split("CDPATH", (*tool)->env);
	if (!cdpath)
		return (1);
	i = -1;
	shmoving = check_moving(dest);
	while (cdpath[++i] && shmoving)
	{
		concat_path = concat_multiple((char *[]){cdpath[i], "/", dest, NULL });
		if (access(concat_path, R_OK | X_OK) == 0)
		{
			ret = simple_cd(concat_path, tool, false);
			free(concat_path);
			free_char_etoile_etoile(cdpath);
			return (ret);
		}
		free(concat_path);
	}
	free_char_etoile_etoile(cdpath);
	return (1);
}

int	cd_mentiel(char **cmd, t_tool **tool)
{
	if (cmd[1] && cmd[2])
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	if (!cmd[1])
		return (cd_home(tool));
	else if (ft_strcmp(cmd[1], "-") == 0 && env_contain("OLDPWD", (*tool)->env))
		return (simple_cd(ft_strdup(env_getval("OLDPWD", (*tool)->env))
				, tool, true));
	else if (check_cdpath(cmd[1], tool) == 0)
		return (0);
	return (simple_cd(cmd[1], tool, false));
}
