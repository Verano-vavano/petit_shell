/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ints.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:59:27 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/11 12:39:59 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printfd.h"

int ft_putulnbr_fd(int fd, unsigned long nbr)
{
	int ttl_wrtn;

	ttl_wrtn = 1;
	if (nbr > 9)
		ttl_wrtn += ft_putunbr_fd(fd, nbr);
	ft_putchar_fd(fd, (nbr % 10) + 48);
	return (ttl_wrtn);
}

int ft_putunbr_fd(int fd, unsigned int nbr)
{
	int ttl_wrtn;

	ttl_wrtn = 1;
	if (nbr > 9)
		ttl_wrtn += ft_putunbr_fd(fd, nbr);
	ft_putchar_fd(fd, (nbr % 10) + 48);
	return (ttl_wrtn);
}


int ft_putnbr_fd(int fd, int nbr)
{
	int ttl_wrtn;

	ttl_wrtn = 1;
	if (nbr == INT_MIN)
		return(ft_putstr_fd(fd, "-2147483648"));
	if (nbr < 0)
	{
		ttl_wrtn += ft_putchar_fd(fd, '-');
		nbr = nbr * -1;
	}
	if (nbr > 9)
		ttl_wrtn += ft_putnbr_fd(fd, nbr / 10);
	ft_putchar_fd(fd, (nbr % 10) + 48);
	return (ttl_wrtn);
}
