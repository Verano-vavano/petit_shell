/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mentiellement_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:35:48 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/06 15:45:15 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	change_oldpwd(t_env **env)
{
	t_env	*pwd;
	t_env	*old_pwd;

	pwd = 0;
	old_pwd = 0;
	if (env_contain("PWD", *env))
		pwd = env_getptr("PWD", *env);
	if (env_contain("OLDPWD", *env))
		old_pwd = env_getptr("OLDPWD", *env);
	if (!pwd || !pwd->value || !pwd->value[0])
		return ;
	if (old_pwd && old_pwd->value && *(old_pwd->value))
		free(old_pwd->value[0]);
	if (!old_pwd)
	{
		old_pwd = ft_calloc(1, sizeof (t_env));
		if (!old_pwd)
			return ;
		old_pwd->value = ft_calloc(2, sizeof (char *));
		if (!old_pwd->value)
		{
			free(old_pwd);
			return ;
		}
		old_pwd->key = ft_strdup("OLDPWD");
		env_add(old_pwd, env);
	}
	old_pwd->value[0] = ft_strdup(pwd->value[0]);
}

static void	no_behind(char *dest, t_env **env, t_tool **tool)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*temp;

	write(2, "cd: error retrieving current directory: getcwd", 46);
	write(2, ": ", 2);
	perror("cannot access parent directories");
	pwd = env_getptr("PWD", *env);
	old_pwd = env_getptr("OLDPWD", *env);
	if (!old_pwd)
		return ;
	if (pwd && pwd->value && pwd->value[0])
		free(pwd->value[0]);
	else
	{
		pwd = ft_calloc(1, sizeof (t_env));
		if (!pwd)
			return ;
		pwd->value = ft_calloc(2, sizeof (char *));
		if (!pwd->value)
		{
			free(pwd);
			return ;
		}
		pwd->key = ft_strdup("PWD");
		env_add(pwd, env);
	}
	temp = ft_strjoin(old_pwd->value[0], "/");
	if (!temp)
		return ;
	pwd->value[0] = ft_strjoin(temp, dest);
	(*tool)->cwd = ft_strdup(pwd->value[0]);
	free(temp);
}

void	change_pwd(char *dest, t_tool **tool)
{
	char	*cwd;
	t_env	*pwd;

	cwd = getcwd(NULL, 0);
	if (!cwd && ft_strcmp(dest, "..") == 0)
		no_behind(dest, &((*tool)->env), tool);
	else if (!cwd)
		perror("No destination directory");
	else
	{
		pwd = env_getptr("PWD", (*tool)->env);
		if (pwd)
			free(pwd->value[0]);
		else
		{
			pwd = ft_calloc(1, sizeof (t_env));
			if (!pwd)
				return ;
			pwd->value = ft_calloc(2, sizeof (char *));
			if (!pwd->value)
			{
				free(pwd);
				return ;
			}
			pwd->key = ft_strdup("PWD");
			env_add(pwd, &((*tool)->env));
			}
		pwd->value[0] = cwd;
		(*tool)->cwd = ft_strdup(cwd);
	}
	return ;
}
