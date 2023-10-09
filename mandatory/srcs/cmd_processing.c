/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:51:38 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/09 17:51:48 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

long	cmd_processing(char *line, t_tool *tool, bool add_line)
{
	t_command	*lexed;
	int			heredoc_no;
	long		rt_val;

	if (!line || !(*line))
	{
		if (line)
			free(line);
		return (0);
	}
	lexed = spliter_init(&line, add_line, tool);
	free(line);
	if (!lexed)
		return (2);
	if (!lexed->content)
	{
		free(lexed);
		return (0);
	}
	rt_val = line_beauty(lexed, tool);
	if (rt_val)
		return (rt_val);
	heredoc_no = 0;
	rt_val = exec_loop(lexed, tool, &heredoc_no);
	return (exit_processing(lexed, tool->rt_val));
}
