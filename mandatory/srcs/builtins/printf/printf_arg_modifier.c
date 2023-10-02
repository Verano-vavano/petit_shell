/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_arg_modifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 01:57:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/02 02:46:52 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "printf.h"

static char	*transform_to_field_size(char *arg, long len, t_printf_flags flags)
{
	char	*to_complete;
	char	*new_arg;

	to_complete = ft_calloc(flags.field_length - len + 1, sizeof (char));
	if (!to_complete)
		return (arg);
	if (flags.zero && !flags.minus
		&& (flags.format == 'd' || flags.format == 'i'
			|| flags.format == 'x' || flags.format == 'X'))
		fill_array(to_complete, '0', flags.field_length - len);
	else
		fill_array(to_complete, ' ', flags.field_length - len);
	if (flags.minus)
		new_arg = ft_strjoin(arg, to_complete);
	else if ((flags.format == 'x' || flags.format == 'X') && flags.sharp)
		new_arg = ft_strreplace(arg, 2, 0, to_complete);
	else
		new_arg = ft_strjoin(to_complete, arg);
	free(to_complete);
	if (new_arg)
	{
		free(arg);
		return (new_arg);
	}
	return (arg);
}

static char	*convert_arg_to_flags(char *arg, t_printf_flags flags)
{
	if (flags.sharp)
		arg = sharp_it(arg, flags.format);
	if (flags.space && !flags.plus)
		arg = add_pos(arg, flags.format, " ");
	else if (flags.plus)
		arg = add_pos(arg, flags.format, "+");
	return (arg);
}

static char	*convert_arg_to_accurate(char *arg, t_printf_flags flags)
{
	size_t	len;

	if (flags.accuracy == -1 || !arg)
		return (arg);
	len = ft_strlen(arg);
	if (flags.format == 's' && len > (size_t) flags.accuracy)
		arg[flags.accuracy] = '\0';
	else if ((flags.format == 'd' || flags.format == 'i'
			|| flags.format == 'x' || flags.format == 'X')
		&& len < (size_t) flags.accuracy)
		arg = make_it_bigger(arg, len, flags.accuracy);
	return (arg);
}

static char	*convert_arg_to_length(char *arg, t_printf_flags flags)
{
	long	len;

	len = ft_strlen(arg);
	if (len < flags.field_length)
		arg = transform_to_field_size(arg, len, flags);
	return (arg);
}

char	*modify_arg(char *arg, t_printf_flags flags, int *ret)
{
	arg = convert_arg_to_format(arg, flags.format, ret);
	if (arg)
		arg = convert_arg_to_accurate(arg, flags);
	if (arg)
		arg = convert_arg_to_flags(arg, flags);
	if (arg)
		arg = convert_arg_to_length(arg, flags);
	return (arg);
}
