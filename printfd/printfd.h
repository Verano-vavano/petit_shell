/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:48:35 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/11 12:39:17 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTFD_H
# define PRINTFD_H

#include <limits.h>
#include <unistd.h>

int	ft_putchar_fd(int fd, char c);
int ft_putstr_fd(int fd, char *str);
int ft_putnbr_fd(int fd, int nbr);
int ft_putunbr_fd(int fd, unsigned int nbr);
int ft_putulnbr_fd(int fd, unsigned long nbr);

#endif
