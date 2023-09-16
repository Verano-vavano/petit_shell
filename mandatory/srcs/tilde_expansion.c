/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:00:49 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/16 16:34:40 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	tilde_it(t_command *cmd, char *tilde, char *pwd, char *opwd)
{
	char	*temp;
	char	*replacer;
	int		to_replace;

	replacer = NULL;
	to_replace = 1 + (cmd->content[1] == '+' || cmd->content[1] == '-');
	if (!cmd)
		return ;
	if (cmd->content[0] == '~' && cmd->content[1] == '+' && pwd)
		replacer = pwd;
	else if (cmd->content[0] == '~' && cmd->content[1] == '-' && opwd)
		replacer = opwd;
	else if (cmd->content[0] == '~' && tilde
		&& cmd->content[1] != '+' && cmd->content[1] != '-')
		replacer = tilde;
	if (cmd->content[0] == '~' && replacer)
	{
		temp = ft_strreplace(cmd->content, 0, to_replace, replacer);
		if (!temp)
			return ;
		free(cmd->content);
		cmd->content = temp;
	}
}

static void	replace_tilde(t_command *cmd, char *tilde, char *pwd, char *opwd)
{
	while (cmd && cmd->next && cmd->purpose != CMD_DELIM)
	{
		tilde_it(cmd, tilde, pwd, opwd);
		cmd = cmd->next;
	}
	if (cmd && cmd->purpose != CMD_DELIM)
		tilde_it(cmd, tilde, pwd, opwd);
}

static int	need_tilde(t_command *cmd)
{
	while (cmd && cmd->next && cmd->purpose != CMD_DELIM)
	{
		if (cmd->content[0] == '~')
			return (1);
		cmd = cmd->next;
	}
	if (cmd && cmd->content[0] == '~' && cmd->purpose != CMD_DELIM)
		return (1);
	return (0);
}

/* Expansions of sort : ~, ~+ and ~-
 * ~n, ~+n and ~-n are not supported (yet ?) */
void	tilde_expansion(t_command *cmd, t_env *env)
{
	char	*temp;
	char	*tilde;
	char	*pwd;
	char	*opwd;
	int		malloqued;

	pwd = NULL;
	opwd = NULL;
	if (!need_tilde(cmd))
		return ;
	temp = env_getval("HOME", env);
	if (temp)
		tilde = temp;
	malloqued = !(temp);
	if (malloqued)
		tilde = get_home(env);
	temp = env_getval("PWD", env);
	if (temp)
		pwd = temp;
	temp = env_getval("OLDPWD", env);
	if (temp)
		opwd = temp;
	replace_tilde(cmd, tilde, pwd, opwd);
	if (malloqued)
		free(tilde);
}
