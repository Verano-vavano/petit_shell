/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:12:20 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/10 15:03:33 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

char	*new_prompt(int n_ps, t_env *env)
{
	char	**temp;
	char	*line;

	temp = 0;
	if (n_ps == 1)
		temp = env_getval("PS1", env);
	else if (n_ps == 2)
		temp = env_getval("PS2", env);
	if (temp && *temp)
		line = readline(temp[0]);
	else if (n_ps == 1)
		line = readline("");
	else if (n_ps == 2)
		line = readline("");
	else
		line = 0;
	return (line);
}
