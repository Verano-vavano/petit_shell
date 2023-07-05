/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_buffers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:23:32 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/05 18:43:55 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_buffers(char *buf1, ...)
{
	va_list	buffers;
	char	*s;

	va_start(buffers, buf1);
	s = buf1;
	while (s != 0)
	{
		free(s);
		s = va_arg(buffers, char *);
	}
	return (0);
}
