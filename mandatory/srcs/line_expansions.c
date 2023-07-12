/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:53:23 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/12 10:40:16 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	expand_cmd(t_command *cmd, t_env *env)
{
	//braces_expansion(str);
	tilde_expansion(cmd, env);
	//parameter_expansion(str, env); // w. word split
	//command_substitution(str, env); // w. word split
	//arithmetic_expansion(str);
	//filename_expansion(str, env);
}
