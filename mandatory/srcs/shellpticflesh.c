/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:08:44 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/06 10:13:18 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "libft.h"
#include <stdlib.h>

int	cmd_processing(char *line)
{
	t_command	*lexed;

	lexed = spliter_init(line);
	if (!lexed || understand_the_line(lexed))
		return (1);
	if (here_doc(lexed))
		return (1);
	if (ft_strcmp("hell", lexed->content) == 0)
		metal_injection();
	else if (ft_strcmp("exit", lexed->content) == 0)
		exit_hell(lexed);
	else if (ft_strcmp("echo", lexed->content) == 0)
		echo_des_enfers(lexed->next);
	line_expansions(lexed);
	//execute_the_line(lexed);
	unlink_heredocs(lexed);
	free_linked_list(lexed);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)ac;
	(void)av;
	(void)env;
	while (42)
	{
		line = readline(PS1);
		if (!line || !(*line))
			continue ;
		cmd_processing(line);
	}
}
