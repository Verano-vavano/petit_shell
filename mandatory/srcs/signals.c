/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:23:01 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/30 16:48:29 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	sig_main(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("%s", CLEAR_LINE);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_catch(int sig)
{
	g_sig_rec = sig;
}

void	heredoc_handle(int sig)
{
	printf("\n");
	rl_replace_line("", 0);
	signal(sig, SIG_DFL);
	kill(ft_getpid(), sig);
}
