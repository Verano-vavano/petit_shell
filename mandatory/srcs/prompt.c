/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:12:20 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/14 11:15:33 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	execute_prompt_command(t_env *env)
{
	char	*temp;
	char	*command;
	t_tool	*empty_tool;

	temp = env_getval("PROMPT_COMMAND", env);
	if (!temp)
		return ;
	command = ft_strdup(temp);
	if (!command)
		return ;
	empty_tool = ft_calloc(1, sizeof (t_tool));
	if (!empty_tool)
		return ;
	empty_tool->env = env;
	cmd_processing(command, empty_tool, false);
	free(empty_tool);
}

char	*new_prompt(int n_ps, t_env *env)
{
	char	*temp;
	char	*line;

	if (n_ps == 1)
		execute_prompt_command(env);
	temp = NULL;
	if (n_ps == 1)
		temp = env_getval("PS1", env);
	else if (n_ps == 2)
		temp = env_getval("PS2", env);
	if (temp && *temp)
		line = readline(temp);
	else if (n_ps == 1)
		line = readline("");
	else if (n_ps == 2)
		line = readline("");
	else
		line = NULL;
	return (line);
}
