/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mentiellement_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:35:48 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/22 13:03:02 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"
#include <string.h>
#include <unistd.h>

static t_env	*add_to_env(char *key, t_env **env)
{
	t_env	*ptr;

	ptr = ft_calloc(1, sizeof (t_env));
	if (!ptr)
		return (0);
	ptr->value = ft_calloc(2, sizeof (char *));
	if (!ptr->value)
	{
		free(ptr);
		return (0);
	}
	ptr->key = ft_strdup(key);
	env_add(ptr, env);
	return (ptr);
}

void	change_oldpwd(t_env **env)
{
	t_env	*pwd;
	t_env	*old_pwd;

	pwd = NULL;
	old_pwd = NULL;
	if (env_contain("PWD", *env))
		pwd = env_getptr("PWD", *env);
	if (env_contain("OLDPWD", *env))
		old_pwd = env_getptr("OLDPWD", *env);
	if (!pwd || !pwd->value || !pwd->value[0])
		return ;
	if (old_pwd && old_pwd->value && *old_pwd->value)
		free(old_pwd->value);
	if (!old_pwd)
		old_pwd = add_to_env("OLDPWD", env);
	old_pwd->value = ft_strdup(pwd->value);
}

static void	no_behind(char *dest, t_env **env, t_tool **tool)
{
	t_env	*pwd;
	t_env	*old_pwd;

	printfd(STDERR_FILENO, "cd: error retrieving current directory: getcwd: ");
	perror("cannot access parent directories");
	pwd = env_getptr("PWD", *env);
	old_pwd = env_getptr("OLDPWD", *env);
	if (!old_pwd)
		return ;
	if (pwd && pwd->value)
		free(pwd->value);
	else
		env_add(env_new_specific("PWD", NULL, false), env);
	pwd = env_getptr("PWD", *env);
	pwd->value = concat_multiple((char *[]){old_pwd->value, "/", dest, NULL});
	(*tool)->cwd = ft_strdup(pwd->value);
}

void	change_pwd(char *dest, t_tool **tool)
{
	char	*cwd;
	t_env	*pwd;

	cwd = getcwd(NULL, 0);
	if ((*tool)->cwd)
	{
		free((*tool)->cwd);
		(*tool)->cwd = NULL;
	}
	if (!cwd)
		no_behind(dest, &((*tool)->env), tool);
	else
	{
		pwd = env_getptr("PWD", (*tool)->env);
		if (pwd)
			free(pwd->value);
		else
			pwd = add_to_env("PWD", &((*tool)->env));
		pwd->value = cwd;
		(*tool)->cwd = ft_strdup(cwd);
	}
	return ;
}
