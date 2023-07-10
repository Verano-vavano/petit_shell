/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellpticflesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 11:08:44 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/10 08:17:06 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "libft.h"
#include <stdlib.h>

int	cmd_processing(char *line, t_env *env)
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
	else if (ft_strcmp("env", lexed->content) == 0)
		env_infernal(env);
	else if (ft_strcmp("export", lexed->content) == 0)
		les_ex_portes_de_lenfer(lexed, env);
	line_expansions(lexed);
	execute_the_line(lexed);
	unlink_heredocs(lexed);
	free_command(lexed);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	*env;

	(void)ac;
	(void)av;
	env = env_processing(envp);
	while (42)
	{
		line = readline(PS1);
		if (!line || !(*line))
			continue ;
		cmd_processing(line, env);
	}
}
