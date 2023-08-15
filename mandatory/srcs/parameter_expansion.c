/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:17:36 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/15 13:07:17 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"

// if not found expand to \0
// TODO pour le moment l'expansion ne prend que la premiere valeur du char **
// mais que se passe t'il si on cherche a expand $PATH
// faire des strcat en boucle?
// TODO fix coredump quand je fais cette commande
// CD $DKASJDLKAJ
// la variable n'existe pas et ca cause un probleme
void	expand_variable(t_command *cmd, t_env *env)
{
	char *variable;
	char **new_val;

	variable = cmd->content + 1;
	if (env_contain(variable, env))
		new_val = env_getval(variable, env);
	else
		new_val = NULL;
	free(cmd->content);
	cmd->content = NULL;
	if (new_val)
		cmd->content = ft_strdup(new_val[0]);
}

void	parameter_expansion(t_command *cmd, t_env *env)
{

	printf("param expansion, cmd = %s\n",cmd->content);
	while(cmd)
	{
		if (*cmd->content == '$')
			expand_variable(cmd, env);
		cmd = cmd->next;
	}
}
