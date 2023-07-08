/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:17:54 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/08 16:50:48 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

t_command	*init_command_arg(t_command *start)
{
	t_command	*new_arg;

	new_arg = ft_calloc(1, sizeof (t_command));
	if (new_arg == 0)
	{
		free_command(start);
		return (0);
	}
	return (new_arg);
}
