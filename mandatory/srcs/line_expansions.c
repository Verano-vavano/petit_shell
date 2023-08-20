/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:53:23 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/20 23:27:12 by hdupire          ###   ########.fr       */
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
	int			ret;

	braces_expansion(cmd);
	tilde_expansion(cmd, env);
	parameter_expansion(cmd, env);
	ret = command_substitution(cmd, env);
	if (ret >= 0)
		return (ret);
	return (-1);
}
