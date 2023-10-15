/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 09:49:19 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/15 09:51:01 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

bool	is_spc(char c)
{
	return (c == ' ' || (unsigned)c - '\t' < 5);
}

bool	is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_sign(char c)
{
	return (c == '-'
		|| c == '+'
		|| c == '*'
		|| c == '/');
}
