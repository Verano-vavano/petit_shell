/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:19:57 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/08 16:18:50 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
// check for '(())' construct in given string
bool is_math(const char *str)
{
	while(*str)
	{
		if (*str == '(' && *(str + 1) == '(')
		{
			str += 2;
			while(*str)
			{
				if (*str == ')' && *(str + 1) == ')')
					return (true);
				str++;
			}
		}
		else
			str++;
	}
	return (false);
}
