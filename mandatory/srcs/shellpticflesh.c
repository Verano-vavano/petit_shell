/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:08:44 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/05 13:59:44 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "libft.h"
#include <stdlib.h>

int	cmd_processing(char *line)
{
	t_command	*lexed;

	if (!ft_strcmp(line, "exit"))
	{
		system("leaks minishell");
		exit(0);
	}
	lexed = spliter_init(line);
	if (!lexed || understand_the_line(lexed))
		return (1);
	if (here_doc(lexed))
		return (1);
	if (ft_strcmp("hell", lexed->content) == 0)
		metal_injection();
	line_expansions(lexed);
	//execute_the_line(lexed);
	unlink_heredocs(lexed);
	free_linked_list(lexed);
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
		line = readline(PS1);
		if (!line || !(*line))
			continue ;
		cmd_processing(line);
	}
}
