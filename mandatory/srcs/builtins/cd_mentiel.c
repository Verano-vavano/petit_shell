/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mentiel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:34:33 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/15 20:45:26 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	update_cwd(t_env *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	env_update(cwd, env, "PWD");
	free(cwd);
}

// oldpwd prend la valeur de l'ancien dir
// oldpwd = pwd
// if !pwd then !oldpwd
// unset PWD && cd ..
// pwd deviens locale... wtf 
void	cd_home(t_env *env)
{
	char	**home;

	home = env_getval("HOME", env);
	if (home == NULL)
		printf("cd: HOME not set\n");
	else
		chdir(home[0]);
}

//
void	cd_absolute(t_env *env, char *dest)
{
	printf("dest = %s\n", dest);
	if (chdir(dest) < 0)
		printf("cd: %s: No such file or directory\n", dest);
	else
		update_cwd(env);
}

int		cd_and_print(char *path)
{
	int	did_cd;

	if (chdir(path))
	{
		printf("%s\n",path);
		did_cd = 1;
	}
	else
		did_cd = 0;
	free(path);
	return (did_cd);
}

// d'abord CDPATH
// puis
// relatif
// sinon ex pas
void	cd_relative(t_env *env, char *dest)
{
	t_env	*cdpath;
	int		i;
	int		did_cd;

	cdpath = env_getptr("CDPATH", env);
	if (!cdpath)
		printf("C'est NULLL\n");
	else
		for (int i = 0; cdpath->value[i]; i++)
			printf("alors val = %s\n", cdpath->value[i]);
	//for (int i = 0);
	if (chdir(dest) > 0)
	did_cd = 0;
	if (cdpath)
	{
		i = -1;
		while(cdpath->value[++i])
		{
			did_cd = cd_and_print(ft_strjoin(cdpath->value[i], dest));
			if (did_cd)
				break ;
		}
	}
	if (!did_cd)
		printf("did not cd\n");
	else
		printf("wow i did cd!!!\n");
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
