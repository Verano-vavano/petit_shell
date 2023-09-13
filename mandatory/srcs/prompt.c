/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:12:20 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/13 11:05:36 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

// TODO getval maybe redo this function
char	*new_prompt(int n_ps, t_env *env)
{
	char	*temp;
	char	*line;

	temp = NULL;
	if (n_ps == 1)
		temp = env_getval("PS1", env);
	else if (n_ps == 2)
		temp = env_getval("PS2", env);
	if (temp && *temp)
		line = readline(temp);
	else if (n_ps == 1)
		line = readline("");
	else if (n_ps == 2)
		line = readline("");
	else
		line = NULL;
	return (line);
}
