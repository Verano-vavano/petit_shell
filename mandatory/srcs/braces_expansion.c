/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:01:48 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/11 18:52:02 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	add_to_chain(t_command *cmd, int *se, int *nodes, char *org)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	t_command	*new_cmd;
	int		repl_index;

	repl_index = nodes[2];
	if (repl_index)
	{
		while (repl_index != 1)
		{
			cmd = cmd->next;
			repl_index--;
		}
		new_cmd = ft_calloc(1, sizeof (t_command));
		new_cmd->purpose = COMMAND;
		if (cmd->next)
			new_cmd->next = cmd->next;
		cmd->next = new_cmd;
		cmd = cmd->next;
	}
	temp = ft_strndup(org, se[0]);
	if (!temp)
		return ;
	temp2 = ft_strndup(org + nodes[1] + 1, nodes[0] - nodes[1] - 1);
	if (!temp2)
	{
		free(temp);
		return ;
	}
	temp3 = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	if (!temp3)
		return ;
	temp = ft_strjoin(temp3, org + se[1] + 1);
	free(temp3);
	if (temp)
	{
		free(cmd->content);
		cmd->content = temp;
	}
}

static int	coma_brace_expansion(t_command *cmd, int *start_end)
{
	char	*org;
	char	quoted;
	int		nodes[3];

	org = ft_strdup(cmd->content);
	if (!org)
		return (1);
	quoted = 0;
	nodes[0] = start_end[0];
	nodes[1] = start_end[0];
	nodes[2] = 0;
	while (org[nodes[0]] && !(org[nodes[0]] == '}' && org[nodes[0] - 1] != '\\'))
	{
		quoted = is_quoted(org, nodes[0], quoted);
		if (!quoted && org[nodes[0]] == ',' && org[nodes[0] - 1] != '\\')
		{
			add_to_chain(cmd, start_end, nodes, org);
			nodes[2]++;
			nodes[1] = nodes[0];
		}
		nodes[0]++;
	}
	add_to_chain(cmd, start_end, nodes, org);
	return (0);
}

static int	apply_brace_exp(t_command *cmd, int *indeces)
{
	int		index;
	char	*s;
	char	quoted;

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

static int	check_brace_exp(char *s)
{
	int		quoted;
	bool	doable;
	int		i;

	i = 1;
	quoted = 0;
	doable = false;
	while (s[i])
	{
		quoted = is_quoted(s, i, quoted);
		if (!quoted && (s[i] == ',' || (s[i] == '.' && s[i + 1] == '.')))
			doable = true;
		if (s[i] == '{' && !quoted && s[i - 1] != '\\')
			return (0);
		if (s[i] == '}' && !quoted && doable && s[i - 1] != '\\')
			return (i);
		i++;
	}
	return (0);
}

static int	brace_expand_it(t_command *cmd)
{
	int	expanded;
	int	quoted;
	int	i;
	int	indeces[2];

	expanded = 0;
	i = 0;
	quoted = 0;
	while (cmd->content[i])
	{
		quoted = is_quoted(cmd->content, i, quoted);
		if (cmd->content[i] == '{' && (i == 0 || (cmd->content[i - 1] != '$'
			&& cmd->content[i - 1] != '\\')) && !quoted)
		{
			indeces[1] = i + check_brace_exp(cmd->content + i);
			if (indeces[1] != i)
			{
				if (cmd->purpose >= IN_FILE && cmd->purpose <= HERE_STRING)
					return (some_error(cmd->content, "ambiguous redirect"));
				indeces[0] = i;
				i = apply_brace_exp(cmd, indeces);
				if (i < 0)
					return (1);
				expanded = 1;
				break ;
			}
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

	err_man = 0;
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		if (ft_strchr(cmd->content, '{') && ft_strchr(cmd->content, '}'))
		err_man = brace_expand_it(cmd);
		if (err_man)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}
