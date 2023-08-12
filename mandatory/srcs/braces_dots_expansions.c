/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_dots_expansions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:47:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/11 19:20:19 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	dots_brace_expansion(t_command *cmd, int *se)
{
	int		i;
	char	*s;

	s = cmd->content;
	i = se[0];
	while (i < se[1])
	{
		if (is_quoted(s, i, 0))
			return (0);
	}
	return (0);
}
