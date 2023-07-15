/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:53:23 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/15 18:45:36 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

//braces_expansion(cmd)
//tilde_expansion(cmd, env)
//parameter_expansion(cmd, env); // w. word split
//command_substitution(cmd, env); // w. word split
//arithmetic_expansion(cmd);
//filename_expansion(cmd, env);
int	expand_cmd(t_command *cmd, t_env *env)
{
	int	debug;

	debug = braces_expansion(cmd);
	if (debug)
		return (free_command(cmd));
	tilde_expansion(cmd, env);
	return (0);
}
