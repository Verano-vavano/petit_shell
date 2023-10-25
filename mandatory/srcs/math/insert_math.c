/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:46:31 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/25 16:56:15 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

bool	insert_math(t_command *cmd, char *output, size_t i_start, size_t i_end)
{
	char	*temp;

	temp = ft_strreplace(cmd->content, i_start, i_end - i_start + 2, output);
	if (!temp)
		return (true);
	free(cmd->content);
	free(output);
	cmd->content = temp;
	return (true);
}
