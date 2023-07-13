/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mentiel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:34:33 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/13 17:36:43 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include <unistd.h>

void	update_cwd(t_env *env)
{
	// t_env	*pwd;
	char	**cwd;

	cwd = malloc(sizeof(char *) * 2);
	cwd[0] = getcwd(NULL, 0);
	cwd[1] = NULL;
	update_env("PWD", cwd, env);
}

// oldpwd prend la valeur de l'ancien dir
// oldpwd = pwd
// if !pwd then !oldpwd
// unset PWD && cd ..
// pwd deviens locale... wtf 
void cd_home(t_env *env)
{
	char **home;

	home = get_env_var(env, "HOME");
	if (home == NULL)
		printf("cd: HOME not set\n");
	else
		chdir(home[0]);
}
//
void cd_absolute(t_env *env, char *dest)
{
	printf("dest = %s\n",dest);
	if (chdir(dest) < 0)
		printf("cd: %s: No such file or directory\n", dest);
	else
		update_cwd(env);
}

// d'abord CDPATH
// puis
// relatif
// sinon ex pas
void cd_relative(t_env *env, char *dest)
{
	printf("cd relatif\n");
	if (chdir(dest) > 0)
	{
	}
	(void)env;
	(void)dest;
}

void	cd_mentiel(t_command *lexed, t_env *env)
{
	lexed = lexed->next;
	if (!lexed)
		cd_home(env);
	else if (lexed->content[0] == '/')
		cd_absolute(env, lexed->content);
	else
		cd_relative(env, lexed->content);
}
