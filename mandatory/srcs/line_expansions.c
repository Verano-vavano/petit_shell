/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_expansions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:53:23 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/07 09:52:16 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	expand_cmd(t_command *cmd, t_tool *tool)
{
	int			ret;

	ret = braces_expansion(cmd);
	if (ret < 0)
		return (1);
	tilde_expansion(cmd, tool->env);
	parameter_expansion(cmd, tool);
	ret = command_substitution(cmd, tool->env);
	if (ret >= 0)
		return (ret);
	filename_expansion(cmd);
	return (-1);
}
