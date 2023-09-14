/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:12:20 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/14 17:23:26 by hdupire          ###   ########.fr       */
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
