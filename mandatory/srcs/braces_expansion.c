/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:01:48 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/15 18:44:19 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	apply_brace_exp(t_command *cmd, int i)
{
	char	*s;
	char	quoted;

	s = cmd->content;
	quoted = 0;
	(void) cmd;
	(void) i;
	return (0);
}

static int	check_brace_exp(char *s)
{
	int		quoted;
	bool	doable;
	int		i;

	i = 0;
	quoted = 0;
	doable = false;
	while (s[i])
	{
		quoted = is_quoted(s, i, quoted);
		if (!quoted && (s[i] == ',' || (s[i] == '.' && s[i + 1] == '.')))
			doable = true;
		if (s[i] == '}' && !quoted && doable)
			return (1);
		i++;
	}
	return (0);
}

static int	brace_expand_it(t_command *cmd)
{
	int	expanded;
	int	quoted;
	int	i;

	expanded = 0;
	i = 0;
	quoted = 0;
	while (cmd->content[i])
	{
		quoted = is_quoted(cmd->content, i, quoted);
		if (cmd->content[i] == '{' && (i == 0 || cmd->content[i - 1] != '$')
			&& !quoted && check_brace_exp(cmd->content + i))
		{
			i = apply_brace_exp(cmd, i);
			if (i < 0)
				return (1);
			expanded = 1;
			break ;
		}
		i++;
	}
	if (expanded)
		brace_expand_it(cmd);
	return (0);
}

/* Expansions of sort l{o,a,i}l and l{0..5..2}
 * l{o,a,i}l -> lol lal lil
 * l{0..5..2} -> 0 2 4
 * also manages ambiguous redirects such as >{l,o} and bad substitutions */
int	braces_expansion(t_command *cmd)
{
	int	err_man;

	while (cmd)
	{
		err_man = brace_expand_it(cmd);
		if (err_man)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}
