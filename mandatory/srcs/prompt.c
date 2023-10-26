/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:12:20 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/26 15:41:10 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

// Applies parameter and command expansions to PS
static char	*ps_basic_expansion(char *ps, t_tool *tool)
{
	t_command	ps_cmd;

	ps_cmd.content = ps;
	if (!ps_cmd.content)
		return (0);
	ps_cmd.purpose = PS_EXP;
	ps_cmd.next = NULL;
	parameter_expansion(&ps_cmd, tool);
	command_substitution(&ps_cmd, tool->env, true, 0);
	return (ps_cmd.content);
}

// Printed before every command
void	print_ps0(t_tool *tool)
{
	char	*ps0;
	char	*ps_expanded;

	ps0 = env_getval("PS0", tool->env);
	if (ps0)
		ps0 = ft_strdup(ps0);
	if (ps0)
	{
		ps_expanded = ps_cool_expansion(ps0, tool);
		if (ps_expanded)
			ps_expanded = ps_basic_expansion(ps_expanded, tool);
		if (ps_expanded)
		{
			write(1, ps_expanded, ft_strlen(ps_expanded));
			free(ps_expanded);
		}
		else
			write(1, ps0, ft_strlen(ps0));
	}
}

// Prompt_command is executed before every command
static void	execute_prompt_command(t_tool *tool)
{
	char	*temp;
	char	*command;
	long	save_ret;

	if (!tool)
		return ;
	temp = env_getval("PROMPT_COMMAND", tool->env);
	if (!temp || !(*temp))
		return ;
	command = ft_strdup(temp);
	if (!command)
		return ;
	save_ret = tool->rt_val;
	cmd_processing(command, tool, false);
	tool->rt_val = save_ret;
}

// PS1 : Main read
// PS2 : Secondary read
char	*new_prompt(int n_ps, t_tool *tool)
{
	char	*temp;
	char	*line;

	temp = 0;
	if (n_ps == 1)
		execute_prompt_command(tool);
	if (n_ps == 1)
		temp = ft_strdup(env_getval("PS1", tool->env));
	else
		temp = ft_strdup(env_getval("PS2", tool->env));
	if (temp)
	{
		temp = ps_cool_expansion(temp, tool);
		if (temp)
			temp = ps_basic_expansion(temp, tool);
	}
	if (temp)
	{
		line = readline(temp);
		free(temp);
	}
	else
		line = readline("");
	return (line);
}
