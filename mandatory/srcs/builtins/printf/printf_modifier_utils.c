/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_modifier_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 02:13:35 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/02 02:49:26 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "printf.h"

static bool	not_just_zero(char *s)
{
	while (*s)
	{
		if (*s != '0')
			return (true);
		s++;
	}
	return (false);
}

char	*sharp_it(char *arg, char format)
{
	char	*temp;

	temp = 0;
	if (format == 'x' && arg && not_just_zero(arg))
		temp = ft_strjoin("0x", arg);
	else if (format == 'X' && arg && not_just_zero(arg))
		temp = ft_strjoin("0X", arg);
	if (temp)
	{
		free(arg);
		return (temp);
	}
	return (arg);
}

void	fill_array(char *s, char c, long size)
{
	size--;
	while (size >= 0)
	{
		s[size] = c;
		size--;
	}
}

char	*make_it_bigger(char *arg, size_t len, size_t accuracy)
{
	char	*zeroes;
	char	*new_arg;
	long	size;

	size = (long) accuracy - len;
	zeroes = ft_calloc(size + 1, sizeof (char));
	if (!zeroes)
		return (arg);
	fill_array(zeroes, '0', size);
	new_arg = ft_strjoin(zeroes, arg);
	free(zeroes);
	if (!new_arg)
		return (arg);
	free(arg);
	return (new_arg);
}

char	*add_pos(char *arg, char format, char *to_add)
{
	char	*temp;

	temp = 0;
	if ((format == 'd' || format == 'i') && arg && arg[0] != '-')
		temp = ft_strjoin(to_add, arg);
	if (temp)
	{
		free(arg);
		return (temp);
	}
	return (arg);
}
