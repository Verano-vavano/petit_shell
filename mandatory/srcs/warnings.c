/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warnings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:13:33 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/10 16:21:06 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	warning_heredoc_eof(int lines, char *eof)
{
	char	*n;
	char	safety;

	write(2, "warning: here_document at line ", 31);
	n = ft_itoa(lines);
	if (n)
	{
		write(2, n, ft_strlen(n));
		free(n);
	}
	else
	{
		safety = '0' + (lines % 10);
		write(2, &safety, 1);
	}
	write(2, " delimited by end-of-file (wanted `", 35);
	write(2, eof, ft_strlen(eof));
	write(2, "')\n", 3);
}
