/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_subst_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:41:08 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/16 13:45:48 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	replacer_cmd(t_command *cmd, int *se, int *ret, t_env *env)
{
	char	*out;

	dup2(se[3], STDOUT_FILENO);
	out = get_output(se + 4);
	if (out && *out && cmd->purpose != VAR_ASSIGN && cmd->purpose != PS_EXP)
	{
		if (word_split(cmd, out, se, env))
			*ret = -120;
	}
	else if (cmd->purpose != VAR_ASSIGN && cmd->purpose != PS_EXP)
	{
		if (word_split(cmd, "\0", se, env))
			*ret = -120;
	}
	else
		cmd->content = ft_strreplace(cmd->content, se[0], se[1] + 1, out);
	if (out)
		free(out);
}

int	command_it(char *cmd_sent, int *se, t_command *cmd, t_env *env)
{
	t_tool	*empty_tool;
	int		ret;

	empty_tool = ft_calloc(1, sizeof (t_tool));
	if (!empty_tool)
	{
		if (se[2])
			dup2(se[3], STDOUT_FILENO);
		if (cmd_sent)
			free(cmd_sent);
		return (1);
	}
	empty_tool->env = env;
	ret = 1;
	if (cmd_sent)
		ret = cmd_processing(cmd_sent, empty_tool, false);
	printfd(STDOUT_FILENO, "\n");
	free(empty_tool);
	if (se[2])
		replacer_cmd(cmd, se, &ret, env);
	return (ret);
}
