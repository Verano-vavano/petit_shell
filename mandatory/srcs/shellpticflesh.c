/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:08:44 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/04 15:00:22 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	cmd_processing(char *line)
{
	t_command	*lexed;

	lexed = spliter_init(line);
	free(line);
	if (!lexed || understand_the_line(lexed))
		return (1);
	/*if (here_doc(lexed))
		return (1);*/
	//command_expansion(lexed)
	//execute_the_line(lexed);
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
