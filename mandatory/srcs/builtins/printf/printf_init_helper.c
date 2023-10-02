/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_init_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 02:09:00 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/02 02:33:32 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "printf.h"

char	*escape_characters(char *str)
{
	char	*temp;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			temp = replace_escaped(str, i);
			if (temp)
			{
				free(str);
				str = temp;
			}
		}
		i++;
	}
	return (str);
}

static void	null_flags(t_printf_flags *flags)
{
	flags->sharp = 0;
	flags->zero = 0;
	flags->minus = 0;
	flags->space = 0;
	flags->plus = 0;
	flags->field_length = 0;
	flags->accuracy = -1;
}

t_printf_flags	get_printf_flags(char **s)
{
	t_printf_flags	flags;

	null_flags(&flags);
	while (**s)
	{
		if (**s == '#')
			flags.sharp = 1;
		else if (**s == '0')
			flags.zero = 1;
		else if (**s == '-')
			flags.minus = 1;
		else if (**s == ' ')
			flags.space = 1;
		else if (**s == '+')
			flags.plus = 1;
		else
			return (flags);
		(*s)++;
	}
	return (flags);
}
