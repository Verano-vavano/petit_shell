/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:34:35 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/15 17:57:00 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	*replace_home(char *cwd, t_env *env)
{
	char	*home;

	home = get_home(env);
	if (!home)
		return (0);
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		return (ft_strreplace(cwd, 0, ft_strlen(home), "~"));
	else
		return (ft_strdup(cwd));
}

static char	*better_getcwd(t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup(env_getval("PWD", env)));
	return (cwd);
}

char	*get_arranged_cwd(t_env *env, bool only_end)
{
	char	*cwd;
	char	*temp;
	char	*ret;

	cwd = better_getcwd(env);
	if (!cwd)
		return (0);
	if (only_end)
	{
		temp = ft_strrchr(cwd, '/');
		if (temp == cwd && !temp[1])
			ret = ft_strdup("/");
		else
			ret = ft_strdup(temp + 1);
	}
	else
		ret = replace_home(cwd, env);
	free(cwd);
	return (ret);
}
