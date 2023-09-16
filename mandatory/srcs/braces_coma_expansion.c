/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_coma_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:46:42 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/16 13:31:03 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static bool	get_content(t_command *cmd, int *se, int *nodes, char *org)
{
	char		*temp;

	temp = get_braces_ext(se, nodes, org);
	if (temp)
	{
		free(cmd->content);
		cmd->content = temp;
		return (true);
	}
	return (false);
}

static bool	add_to_chain(t_command *cmd, int *se, int *nodes, char *org)
{
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
		if (!new_cmd)
			return (false);
		new_cmd->purpose = COMMAND;
		if (cmd->next)
			new_cmd->next = cmd->next;
		cmd->next = new_cmd;
		cmd = cmd->next;
	}
	return (get_content(cmd, se, nodes, org));
}

static int	cbrace_loop(t_command *cmd, int *se, char *org, int *nodes)
{
	bool	start;

	start = true;
	while (org[nodes[0]])
	{
		nodes[0] += find_end(org + nodes[0] + !start) + !start;
		if (org[nodes[0]] == '}')
			break ;
		if (!add_to_chain(cmd, se, nodes, org))
		{
			free(org);
			return (-1);
		}
		nodes[2]++;
		nodes[1] = nodes[0];
		start = false;
	}
	return (0);
}

int	coma_brace_expansion(t_command *cmd, int *start_end)
{
	char	*org;
	int		nodes[3];

	org = ft_strdup(cmd->content);
	if (!org)
		return (-1);
	nodes[0] = start_end[0] + 1;
	nodes[1] = start_end[0];
	nodes[2] = 0;
	if (cbrace_loop(cmd, start_end, org, nodes))
		return (-1);
	if (!add_to_chain(cmd, start_end, nodes, org))
	{
		free(org);
		return (-1);
	}
	return (0);
}
