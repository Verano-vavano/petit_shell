/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_coma_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:46:42 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/18 17:49:00 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	find_end(char *s)
{
	int	i;
	int	in_braces;
	int	quoted;

	i = 0;
	in_braces = 0;
	quoted = 0;
	while (s[i])
	{
		quoted = is_quoted(s, i, quoted);
		if (!quoted && s[i] == '{' && (i == 0 || s[i - 1] != '\\'))
			in_braces++;
		else if (!quoted && (s[i] == '}' || s[i] == ',') && !in_braces)
			break ;
		else if (!quoted && s[i] == '}' && (i == 0 || s[i - 1] != '\\'))
			in_braces--;
		i++;
	}
	return (i);
}

static char	*get_braces_ext(int *se, int *nodes, char *org)
{
	char	*temp;
	char	*temp2;
	char	*temp3;

	temp = ft_strndup(org, ft_strchr_int(org, '{'));
	if (!temp)
		return (0);
	temp2 = ft_strndup(org + nodes[1] + 1, find_end(org + nodes[1] + 1));
	if (!temp2)
	{
		free(temp);
		return (0);
	}
	temp3 = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	if (!temp3)
		return (0);
	temp = ft_strjoin(temp3, org + se[1] + 1);
	free(temp3);
	return (temp);
}

static void	add_to_chain(t_command *cmd, int *se, int *nodes, char *org)
{
	char		*temp;
	t_command	*new_cmd;
	int			repl_index;

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
	temp = get_braces_ext(se, nodes, org);
	if (temp)
	{
		free(cmd->content);
		cmd->content = temp;
	}
}

int	coma_brace_expansion(t_command *cmd, int *start_end)
{
	char	*org;
	int		nodes[3];
	bool	start;

	org = ft_strdup(cmd->content);
	if (!org)
		return (-1);
	nodes[0] = start_end[0] + 1;
	nodes[1] = start_end[0];
	nodes[2] = 0;
	start = true;
	while (org[nodes[0]])
	{
		nodes[0] += find_end(org + nodes[0] + !start) + !start;
		if (org[nodes[0]] == '}')
			break ;
		add_to_chain(cmd, start_end, nodes, org);
		nodes[2]++;
		nodes[1] = nodes[0];
		start = false;
	}
	add_to_chain(cmd, start_end, nodes, org);
	return (0);
}
