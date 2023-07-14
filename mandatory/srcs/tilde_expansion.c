/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:00:49 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/14 15:49:11 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	tilde_it(t_command *cmd, char *tilde, char *pwd, char *opwd)
{
	char	*temp;
	char	*replacer;
	int		to_replace;

	replacer = 0;
	to_replace = 2;
	if (!cmd)
		return ;
	if (cmd->content[0] == '~' && cmd->content[1] == '+' && pwd)
		replacer = pwd;
	else if (cmd->content[0] == '~' && cmd->content[1] == '-' && opwd)
		replacer = opwd;
	else if (cmd->content[0] == '~' && tilde
		&& cmd->content[1] != '+' && cmd->content[1] != '-')
	{
		to_replace = 1;
		replacer = tilde;
	}
	if (cmd->content[0] == '~' && replacer)
	{
		temp = ft_strreplace(cmd->content, 0, to_replace, replacer);
		free(cmd->content);
		cmd->content = temp;
	}
}

static void	replace_tilde(t_command *cmd, char *tilde, char *pwd, char *opwd)
{
	while (cmd && cmd->next)
	{
		tilde_it(cmd, tilde, pwd, opwd);
		cmd = cmd->next;
	}
	if (cmd)
		tilde_it(cmd, tilde, pwd, opwd);
}

static int	need_tilde(t_command *cmd)
{
	while (cmd && cmd->next)
	{
		if (cmd->content[0] == '~')
			return (1);
		cmd = cmd->next;
	}
	if (cmd && cmd->content[0] == '~')
		return (1);
	return (0);
}

/* Expansions of sort : ~, ~+ and ~-
 * ~n, ~+n and ~-n are not supported (yet ?) */
void	tilde_expansion(t_command *cmd, t_env *env)
{
	char	**temp;
	char	*tilde;
	char	*pwd;
	char	*opwd;
	int		malloqued;

	pwd = 0;
	opwd = 0;
	if (!need_tilde(cmd))
		return ;
	temp = env_getval(env, "HOME");
	if (temp)
		tilde = *temp;
	malloqued = !(temp);
	if (malloqued)
		tilde = rescue_tilde_funk(env);
	temp = env_getval(env, "PWD");
	if (temp)
		pwd = *temp;
	temp = env_getval(env, "OLDPWD");
	if (temp)
		opwd = *temp;
	replace_tilde(cmd, tilde, pwd, opwd);
	if (malloqued)
		free(tilde);
}
