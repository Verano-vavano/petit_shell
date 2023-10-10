/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh_more.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 22:51:03 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/10 18:14:18 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static bool	still_going(t_command *lexed, bool start, long rt_val)
{
	return (lexed && (start
			|| (!ft_strcmp(lexed->content, "&&") && rt_val == 0)
			|| (!ft_strcmp(lexed->content, "||") && rt_val != 0)
			|| (!ft_strcmp(lexed->content, ";"))));
}

long	exec_loop(t_command *lexed, t_tool *tool, int *hd_no)
{
	long	rt_val;
	bool	start;

	rt_val = tool->rt_val;
	start = true;
	while (still_going(lexed, start, rt_val))
	{
		if (lexed->purpose == CMD_DELIM)
			lexed = lexed->next;
		alias_expansion(lexed, tool);
		rt_val = expand_cmd(lexed, tool);
		quote_remove_cmd(lexed);
		if (rt_val < 0)
			rt_val = execute_the_line(lexed, tool, hd_no);
		assign_vars(lexed, &(tool->env));
		while (lexed && lexed->purpose != CMD_DELIM)
			lexed = lexed->next;
		start = false;
		tool->rt_val = rt_val;
	}
	return (rt_val);
}

long	exit_processing(t_command *lexed, long rt_val)
{
	unlink_heredocs(lexed);
	free_command(lexed);
	return (rt_val);
}

long	line_beauty(t_command *lexed, t_tool *tool)
{
	long	ret;

	if (!lexed || !(lexed->content))
		return (1);
	ret = understand_the_line(lexed);
	if (ret)
		return (ret);
	ret = here_doc(lexed, tool);
	if (ret)
		return (ret);
	return (0);
}
