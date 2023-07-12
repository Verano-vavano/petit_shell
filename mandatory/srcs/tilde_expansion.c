/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:00:49 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/12 14:06:50 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	tilde_it(t_command *cmd, char **tilde, char **pwd, char **opwd)
{
	char	*temp;
	char	*replacer;
	int		to_replace;

	replacer = 0;
	to_replace = 2;
	if (cmd->content[0] == '~' && cmd->content[1] == '+' && pwd)
		replacer = *pwd;
	else if (cmd->content[0] == '~' && cmd->content[1] == '-' && opwd)
		replacer = *opwd;
	else if (cmd->content[0] == '~' && tilde
		&& cmd->content[1] != '+' && cmd->content[1] != '-')
	{
		to_replace = 1;
		replacer = *tilde;
	}
	if (cmd->content[0] == '~' && replacer)
	{
		temp = ft_strreplace(cmd->content, 0, to_replace, replacer);
		free(cmd->content);
		cmd->content = temp;
	}
}

static void	replace_tilde(t_command *cmd, char **tilde, char **pwd, char **opwd)
{
	while (cmd->next)
	{
		tilde_it(cmd, tilde, pwd, opwd);
		cmd = cmd->next;
	}
	if (cmd)
		tilde_it(cmd, tilde, pwd, opwd);
}

void	tilde_expansion(t_command *cmd, t_env *env)
{
	char	**tilde;
	char	**pwd;
	char	**opwd;

	(void) cmd;
	tilde = get_env_var(env, "HOME");
	pwd = get_env_var(env, "PWD");
	opwd = get_env_var(env, "OLDPWD");
	/*if (!is_set)
		to_sub = get_username();*/
	/*if (!is_set)
		get_path_from_username();*/
	replace_tilde(cmd, tilde, pwd, opwd);
}
