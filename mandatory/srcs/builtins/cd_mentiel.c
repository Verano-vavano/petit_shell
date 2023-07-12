/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_mentiel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:34:33 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/12 17:44:29 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include <unistd.h>



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
// void cd_absolute(t_env *env, char *destination)
// {
// 	printf("dest = %s\n",destination);
// 	if (chdir(destination) < 0)
// 		printf("cd: %s: No such file or directory\n", destination);
// 	else
// 		update_cwd(env);
// }

void	cd_mentiel(t_command *lexed, t_env *env)
{
	(void)lexed;
	(void)env;
	lexed = lexed->next;
	if (!lexed)
		cd_home(env);
	// else if (lexed->content[0] == '/')
	// 	cd_absolute(env, lexed->content);
	// lexed->content == NULL
	//	 cd HOME
	// lexed->content[0] == '/'
	//   absolute_path
	// first char = . || "a-z A-Z"
	//   relative 
	//   cd_path
}
