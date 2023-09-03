/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_exp_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 23:11:51 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/03 23:12:36 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	find_arg_len(char *s, bool brack, char quoted)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!brack && (s[i] < '0' || s[i] > '9') && (s[i] < 'a' || s[i] > 'z')
			&& (s[i] < 'A' || s[i] > 'Z') && s[i] != '_')
			break ;
		else if (!brack && s[i] == quoted)
			break ;
		else if (brack && s[i] == '}')
			break ;
		i++;
	}
	return (i);
}
