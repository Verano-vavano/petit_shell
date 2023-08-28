/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 22:24:00 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/28 22:24:37 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef SYS_nanosleep

int	ft_nanosleep(const struct timespec *req)
{
	long	ret;

	{
		asm (
			"mov %[syscall], %%rax\n"
			"mov %[timer], %%rdi\n"
			"syscall\n"
			"mov %%rax, %[ret]\n"
			: [ret] "=A" (ret)
			: [syscall] "i" (SYS_nanosleep), [timer] "r" (req)
			: "%rax", "%rdi"
		);
	}
	return ((int) ret);
}

#else

int	ft_nanosleep(const struct timespec *req)
{
	(void) req;
	return (-1);
}
#endif
