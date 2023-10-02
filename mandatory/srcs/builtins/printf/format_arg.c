/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 02:00:16 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/02 02:25:08 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "printf.h"

static char	*hexa_it(char *arg, bool maj)
{
	long	long_arg;

	if (is_long(arg, false))
	{
		long_arg = ft_atol(arg);
		return (hexa(long_arg, maj));
	}
	return (0);
}

static char	*change_int(char *arg, int *ret)
{
	if (arg && !is_long(arg, true))
	{
		printfd(ERR, "printf: %s: invalid number\n", arg);
		*ret = 1;
		free(arg);
		arg = 0;
	}
	if (!arg)
		arg = ft_strdup("0");
	return (arg);
}

char	*convert_arg_to_format(char *arg, char format, int *ret)
{
	char	*temp;

	if (format == 'd' || format == 'i' || format == 'x' || format == 'X')
		arg = change_int(arg, ret);
	else if (!arg)
		arg = ft_calloc(1, sizeof (char));
	if (format == 'c')
	{
		if (!arg)
			return (ft_strdup("\0"));
		temp = ft_strndup(arg, 1);
		free(arg);
		return (temp);
	}
	else if (format == 'x' || format == 'X')
	{
		temp = hexa_it(arg, (format == 'X'));
		if (temp)
		{
			free(arg);
			return (temp);
		}
	}
	return (arg);
}
