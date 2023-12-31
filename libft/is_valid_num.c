/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:22:28 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/01 14:36:17 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_valid_num(char *s)
{
	int	i;

	if (!s)
		return (true);
	if (!is_dgt(s[0]) && s[0] != '-' && s[0] != '+')
		return (false);
	i = 1;
	while (s[i])
	{
		if (!is_dgt(s[i]))
			return (false);
		i++;
	}
	return (true);
}
