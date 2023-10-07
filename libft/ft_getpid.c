/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:38:57 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/07 15:17:42 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef SYS_getpid

long	ft_getpid(void)
{
	long	result;

	{
		asm (
			"mov %1, %%rax\n"
			"syscall\n"
			"mov %%rax, %0\n"
			: "=A" (result)
			: "i" (SYS_getpid)
			);
	}
	return (result);
}

#else

long	ft_getpid(void)
{
	return (-1);
}
#endif
