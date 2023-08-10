/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:23:01 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/10 18:43:58 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	sig_main(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("%s", CLEAR_LINE);
		rl_redisplay();
		return ;
	}
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	sig_catch(int sig)
{
	g_sig_rec = sig;
}
