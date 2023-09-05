/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:01:48 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/04 15:44:02 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	brace_expand_it(t_command *cmd);
int	find_closing_brack(char *s);

static int	apply_brace_exp(t_command *cmd, int *indeces)
{
	int		index;
	char	*s;
	char	quoted;

	if (cmd->purpose >= IN_FILE && cmd->purpose <= HERE_STRING)
		return (0 * (some_error(cmd->content, "ambiguous redirect")) - 1);
	s = cmd->content;
	quoted = 0;
	index = indeces[0];
	while (s[index])
	{
		quoted = is_quoted(cmd->content, index, quoted);
		if (!quoted && s[index] == ',' && s[index - 1] != '\\')
			return (coma_brace_expansion(cmd, indeces));
		index++;
	}
	return (dots_brace_expansion(cmd, indeces));
}

int	find_closing_brack(char *s)
{
	int	quoted;
	int	i;
	int	in_braces;

	i = 0;
	quoted = 0;
	in_braces = 0;
	while (s[i])
	{
		quoted = is_quoted(s, i, quoted);
		if (s[i] == '{' && !quoted)
			in_braces++;
		if (s[i] == '}' && !quoted && s[i - 1] != '\\' && !in_braces)
			return (i);
		else if (s[i] == '}')
			in_braces--;
		i++;
	}
	return (-1);
}

static int	check_brace_exp(char *s)
{
	int		quoted;
	int		inside;
	bool	doable;
	int		i;

	i = 1;
	quoted = 0;
	inside = 0;
	doable = false;
	while (s[i])
	{
		quoted = is_quoted(s, i, quoted);
		if (!quoted && (s[i] == ',' || (s[i] == '.' && s[i + 1] == '.')))
			doable = true;
		if (s[i] == '{' && !quoted && s[i - 1] != '\\')
			inside++;
		if (s[i] == '}' && !quoted && doable && s[i - 1] != '\\' && !inside)
			return (i);
		else if (s[i] == '}' && inside)
			inside--;
		i++;
	}
	return (0);
}

int	brace_expand_it(t_command *cmd)
{
	int		i;
	int		ret;
	int		indeces[2];

	i = -1;
	ret = 0;
	while (cmd->content[++i])
	{
		ret = is_quoted(cmd->content, i, ret);
		if (cmd->content[i] == '{' && (i == 0 || (cmd->content[i - 1] != '$'
					&& cmd->content[i - 1] != '\\')) && !ret)
		{
			indeces[1] = i + check_brace_exp(cmd->content + i);
			if (indeces[1] != i)
			{
				indeces[0] = i;
				ret = apply_brace_exp(cmd, indeces);
				if (ret == -1 || ret == -2)
					return (-5);
				ret += brace_expand_it(cmd);
				break ;
			}
		}
	}
	return (0);
}

/* Expansions of sort l{o,a,i}l and l{0..5..2}
 * l{o,a,i}l -> lol lal lil
 * l{0..5..2} -> 0 2 4
 * also manages ambiguous redirects such as >{l,o} and bad substitutions 
 * inner brackets arent functionning as bash, ill see later */
int	braces_expansion(t_command *cmd)
{
	int	err_man;

	err_man = 0;
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		if (ft_strchr(cmd->content, '{') && ft_strchr(cmd->content, '}')
			&& (ft_strchr(cmd->content, '.') || ft_strchr(cmd->content, ',')))
			err_man = brace_expand_it(cmd);
		if (err_man == -1)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}
