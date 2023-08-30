/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:53:23 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/30 16:20:23 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	expand_cmd(t_command *cmd, t_tools *tools)
{
	int			ret;

	braces_expansion(cmd);
	tilde_expansion(cmd, tools->env);
	parameter_expansion(cmd, tools->env);
	ret = command_substitution(cmd, tools->env);
	if (ret >= 0)
		return (ret);
	filename_expansion(cmd);
	return (-1);
}
