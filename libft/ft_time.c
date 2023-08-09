/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 23:35:16 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/30 20:38:51 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef SYS_time

time_t	ft_time(void)
{
	time_t	result;

	{
		asm (
			"mov %1, %%rax\n"
			"syscall\n"
			"mov %%rax, %0\n"
			: "=A" (result)
			: "i" (SYS_time)
			);
	}
	return (result);
}

#else

time_t	ft_time(void)
{
	return (-1);
}
#endif
