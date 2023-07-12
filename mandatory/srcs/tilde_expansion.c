/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:00:49 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/12 12:29:45 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	tilde_it(t_command *cmd, char *tilde)
{
	char	*temp;

	if (cmd->content[0] == '~')
	{
		temp = ft_strreplace(cmd->content, 0, 1, tilde);
		free(cmd->content);
		cmd->content = temp;
	}
}

static void	replace_tilde(t_command *cmd, char *tilde)
{
	while (cmd->next)
	{
		tilde_it(cmd, tilde);
		cmd = cmd->next;
	}
	if (cmd)
		tilde_it(cmd, tilde);
}

void	tilde_expansion(t_command *cmd, t_env *env)
{
	char		*to_sub;
	int			is_set;

	to_sub = 0;
	is_set = get_home(&to_sub, env);
	printf("%d %s\n", is_set, to_sub);
	/*if (!is_set)
		to_sub = get_username();*/
	/*if (!is_set)
		get_path_from_username();*/
	replace_tilde(cmd, to_sub);
}
