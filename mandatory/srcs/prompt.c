/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:12:20 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/15 10:10:12 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	print_ps0(t_env *env)
{
	char	*ps0;

	ps0 = env_getval("PS0", env);
	if (ps0)
		write(1, ps0, ft_strlen(ps0));
}

static void	execute_prompt_command(t_tool *tool)
{
	char	*temp;
	char	*command;

	if (!tool)
		return ;
	temp = env_getval("PROMPT_COMMAND", tool->env);
	if (!temp)
		return ;
	command = ft_strdup(temp);
	if (!command)
		return ;
	cmd_processing(command, tool, false);
}

static char	*ps_expand(char *ps, t_tool *tool)
{
	t_command	ps_cmd;

	ps_cmd.content = ft_strdup(ps);
	if (!ps_cmd.content)
		return (0);
	ps_cmd.purpose = PS_EXP;
	ps_cmd.next = NULL;
	parameter_expansion(&ps_cmd, tool);
	command_substitution(&ps_cmd, tool->env);
	return (ps_cmd.content);
}

char	*new_prompt(int n_ps, t_tool *tool)
{
	char	*temp;
	char	*line;

	if (n_ps == 1)
		execute_prompt_command(tool);
	temp = NULL;
	if (n_ps == 1)
		temp = env_getval("PS1", tool->env);
	else if (n_ps == 2)
		temp = env_getval("PS2", tool->env);
	if (temp && *temp)
	{
		temp = ps_expand(temp, tool);
		if (temp && *temp)
		{
			line = readline(temp);
			free(temp);
			return (line);
		}
	}
	if (n_ps == 1)
		line = readline("");
	else if (n_ps == 2)
		line = readline("");
	else
		line = NULL;
	return (line);
}
