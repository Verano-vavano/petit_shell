/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:08:44 by hdupire           #+#    #+#             */
/*   Updated: 2023/06/30 19:07:55 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	cmd_processing(char *line)
{
	t_command	*lexed;

	add_history(line);
	lexed = understand_the_line(line);
	if (!line || !(*line))
		return (1);
	if (here_doc(lexed))
		return (1);
	//execute_the_line(line);
	free(line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
	while (42)
	{
		line = readline("lol >> ");
		if (!line || !(*line))
			continue ;
		cmd_processing(line);
	}
}
