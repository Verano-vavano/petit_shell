/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:00:15 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 19:05:57 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"

static int	init_termios(struct termios old_term)
{
	struct termios	new_term;

	new_term = old_term;
	new_term.c_lflag &= ~(ICANON | ECHO);
	new_term.c_cc[VMIN] = 0;
	new_term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_term))
		return (1);
	return (0);
}

static int	init_term(void)
{
	int		ret;
	char	*terminal;

	terminal = getenv("TERM");
	if (!terminal)
		return (1);
	ret = tgetent(NULL, terminal);
	if (ret <= 0)
		return (1);
	return (0);
}

int	tetris(char **args)
{
	int				l;
	int				col;
	t_map			*maper;
	struct termios	old_term;

	(void) args;
	maper = ft_calloc(1, sizeof (t_map));
	if ((!maper) | init_term())
		return (1);
	tputs(tgetstr("cl", NULL), 1, putchar);
	l = tgetnum("li");
	col = tgetnum("co");
	if (col < 60 || l < HEIGHT_BOARD + 4)
		return (1);
	if (tcgetattr(STDIN_FILENO, &old_term) || init_termios(old_term))
		return (1);
	maper->fl_map = 2;
	maper->fc_map = (col / 2) - (WIDTH_BOARD + 2);
	maper->actual_declared = false;
	maper->prev = -1;
	draw_outside(maper);
	start_game(maper);
	tputs(tgoto(maper->cm_cap, 0, HEIGHT_BOARD + 4), 1, putchar);
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
	free(maper);
	printf("%s\n", WHITE);
	return (0);
}
