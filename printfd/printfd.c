/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:35 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/11 13:18:23 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printfd.h"
#include <stdarg.h>

int handle_format(int fd, const char *fmt_str, va_list args)
{
	fmt_str++;
	if (*fmt_str == 'd' || *fmt_str == 'i')
		return(ft_putnbr_fd(fd, va_arg(args, int)));
	if (*fmt_str == 'u')
		return (ft_putunbr_fd(fd, va_arg(args, unsigned int)));
	if (*fmt_str == 's')
		return (ft_putstr_fd(fd, va_arg(args, char *)));
	if (*fmt_str == 'c')
		return (ft_putchar_fd(fd, va_arg(args, int)));
	if (*fmt_str == '%')
		return (ft_putchar_fd(fd, '%'));
	if (*fmt_str == 'l' && *fmt_str + 1 && *fmt_str + 1 == 'u')
		return (ft_putulnbr_fd(fd, va_arg(args, unsigned long)));
	return (0);
}

int	printfd(int fd, const char *fmt_str, ...)
{
	int		ttl_wrtn;
	va_list	args;

	ttl_wrtn = 0;
	va_start(args, fmt_str);
	while(*fmt_str)
	{
		if (*fmt_str == '%')
			ttl_wrtn += handle_format(fd, fmt_str, args);
		else
			ttl_wrtn += ft_putchar_fd(fd, *fmt_str);
		fmt_str++;
	}
	va_end(args);
	return (ttl_wrtn);
}
