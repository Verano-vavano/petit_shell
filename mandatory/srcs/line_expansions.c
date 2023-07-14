/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:53:23 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/13 15:43:43 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	expand_cmd(t_command *cmd, t_env *env)
{
	int	debug;

	debug = braces_expansion(cmd);
	if (debug)
		return (free_command(cmd));
	tilde_expansion(cmd, env);
	//parameter_expansion(str, env); // w. word split
	//command_substitution(str, env); // w. word split
	//arithmetic_expansion(str);
	//filename_expansion(str, env);
	return (0);
}
