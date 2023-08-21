/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:53:23 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/21 08:49:41 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

//braces_expansion(cmd) DONE
//tilde_expansion(cmd, env) DONE
//parameter_expansion(cmd, env); SEMI-DONE // w. word split
//command_substitution(cmd, env); DONE // w. word split
//arithmetic_expansion(cmd);
//filename_expansion(cmd);
int	expand_cmd(t_command *cmd, t_env *env)
{
	int			ret;

	braces_expansion(cmd);
	tilde_expansion(cmd, env);
	parameter_expansion(cmd, env);
	ret = command_substitution(cmd, env);
	if (ret >= 0)
		return (ret);
	filename_expansion(cmd);
	return (-1);
}
