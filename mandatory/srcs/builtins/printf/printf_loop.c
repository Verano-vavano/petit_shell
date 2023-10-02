/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 02:28:55 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/02 02:41:25 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "shellpticflesh.h"

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

static int	check_all_good(char *arg, char **m_str, t_printf_flags *flags)
{
	if (!is_valid_format(**m_str, flags))
	{
		printfd(ERR, "printf: `%c': invalid format character\n", **m_str);
		free(arg);
		return (1);
	}
	else if (flags->field_length == -2 || flags->accuracy == -2)
	{
		free(arg);
		return (-1);
	}
	return (0);
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
	ret = check_all_good(arg, m_str, &flags);
	if (ret)
		return (ret == 1);
	ret = 0;
	arg = modify_arg(arg, flags, &ret);
	if (arg)
	{
		printf("%s", arg);
		free(arg);
	}
	return (ret * (-1));
}

static int	convert_init(char **m_str, char *sb, char ***cmd, int *big_ret)
{
	int	ret;

	(*m_str)++;
	if (!(**m_str))
	{
		printfd(ERR, "printf: `%%': missing format character\n");
		free(sb);
		return (1);
	}
	ret = print_correspondingly(m_str, ft_strdup(**cmd));
	if (ret > 0)
	{
		free(sb);
		return (ret);
	}
	else if (ret < 0)
		*big_ret = ret * (-1);
	if (*cmd)
		(*cmd)++;
	return (0);
}

int	printf_loop(char **cmd, char *main_string)
{
	char	*save_base;
	int		ret;
	int		big_ret;

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
			ret = convert_init(&main_string, save_base, &cmd, &big_ret);
			if (ret)
				return (ret);
		}
		else
			printf("%c", *main_string);
		main_string++;
	}
	free(save_base);
	return (big_ret);
}
