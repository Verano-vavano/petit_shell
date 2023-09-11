/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:12:56 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/11 12:19:21 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printfd.h"

int	ft_putchar_fd(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	ft_putstr_fd(int fd, char *str)
{
	int ttl_wrtn;

	ttl_wrtn = 0;
	if (!*str)
		return(ft_putstr_fd(fd, "(null)"));
	while (*str)
		ttl_wrtn += ft_putchar_fd(fd, *str++);
	return (ttl_wrtn);
}
