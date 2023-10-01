/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printferno.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 03:58:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/01 21:21:01 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "printf.h"

static char	*escape_characters(char *str)
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

static t_printf_flags	get_printf_flags(char **s)
{
	t_printf_flags	flags;

	flags.sharp = 0;
	flags.zero = 0;
	flags.minus = 0;
	flags.space = 0;
	flags.field_length = 0;
	flags.accuracy = -1;
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
		else
			return (flags);
		(*s)++;
	}
	return (flags);
}

static bool	is_valid_format(char c, t_printf_flags *flags)
{
	if (c == 'c' || c == 's'
		|| c == 'd' || c == 'i'
		|| c == 'x' || c == 'X')
	{
		flags->format = c;
		return (true);
	}
	return (false);
}

static void	get_length(char **m_str, int *i)
{
	char	*field;
	long	tester;
	int		len_field;

	len_field = 0;
	while ((*m_str) && is_num((*m_str)[len_field]))
		len_field++;
	field = ft_strndup(*m_str, len_field + 1);
	(*m_str) += len_field;
	if (!field)
		return ;
	if (len_field > ft_longlen(INT_MIN))
		(*i) = -2;
	else
	{
		tester = ft_atol(field);
		if (tester > INT_MAX || tester < INT_MIN)
			(*i) = -2;
		else
			(*i) = tester;
	}
	free(field);
}

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

static char	*convert_arg_to_format(char *arg, char format, int *ret)
{
	char	*temp;

	if (format == 'd' || format == 'i' || format == 'x' || format == 'X')
	{
		if (!is_long(arg, true))
		{
			printfd(ERR, "printf: %s: invalid number\n", arg);
			*ret = 1;
		}
		if (!arg)
			arg = ft_strdup("0");
	}
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

static char	*modify_arg(char *arg, t_printf_flags flags, int *ret)
{
	// CONVERTIR ARG SELON FORMAT
	// CONVERTIR SELON LES FLAGS
	// APPLIQUER PRECISION
	// APPLIQUER MIN_FIELD_LEN
	arg = convert_arg_to_format(arg, flags.format, ret);
	(void) flags;
	return (arg);
}

static int	print_correspondingly(char **m_str, char *arg)
{
	t_printf_flags	flags;
	int				ret;

	flags = get_printf_flags(m_str);
	if (is_num(*(*m_str)))
		get_length(m_str, &(flags.field_length));
	if (*(*m_str) == '.')
	{
		(*m_str)++;
		get_length(m_str, &(flags.accuracy));
	}
	if (!is_valid_format(**m_str, &flags))
	{
		printfd(ERR, "printf: `%c': invalid format character\n", **m_str);
		free(arg);
		return (1);
	}
	else if (flags.field_length == -2 || flags.accuracy == -2)
	{
		free(arg);
		return (0);
	}
	ret = 0;
	arg = modify_arg(arg, flags, &ret);
	if (arg)
	{
		printf("%s", arg);
		free(arg);
	}
	return (ret * (-1));
}

static int	printf_loop(char **cmd, char *main_string)
{
	char	*save_base;
	int		i;
	int 	ret;
	int		big_ret;

	i = 2;
	main_string = escape_characters(main_string);
	save_base = main_string;
	big_ret = 0;
	while (*main_string)
	{
		if (*main_string == '%' && *(main_string + 1) == '%')
		{
			main_string++;
			printf("%%");
		}
		else if (*main_string == '%')
		{
			main_string++;
			if (!(*main_string))
			{
				printfd(ERR, "printf: `%%': missing format character\n");
				free(save_base);
				return (1);
			}
			ret = print_correspondingly(&main_string, ft_strdup(cmd[i]));
			if (ret > 0)
			{
				free(save_base);
				return (ret);
			}
			else if (ret < 0)
				big_ret = ret * (-1);
			if (cmd[i])
				i++;
		}
		else
			printf("%c", *main_string);
		main_string++;
	}
	free(save_base);
	return (big_ret);
}

int	printferno(char **cmd)
{
	char	*main_string;
	int		ret;

	main_string = ft_strdup(cmd[1]);
	if (main_string == NULL)
	{
		printfd(ERR, "printf: usage: printf format [arguments]\n");
		return (2);
	}
	ret = printf_loop(cmd, main_string);
	return (ret);
}
