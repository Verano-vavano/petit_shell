/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:00:15 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/20 16:16:02 by hdupire          ###   ########.fr       */
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

static char	get_kb(int fd)
{
	int		r;
	char	c;
	char	readed[1024];
	char	**splited;

	r = read(fd, readed, 1023);
	readed[r] = 0;
	splited = ft_split(readed, '\n');
	r = 0;
	c = 'q';
	while (splited[r])
	{
		if (ft_strncmp(splited[r], "KEYMAP=\"", 8) == 0)
		{
			if (ft_strncmp(splited[r] + 8, "fr", 2) == 0)
				c = 'a';
			break ;
		}
		r++;
	}
	free_char_etoile_etoile(splited);
	close(fd);
	return (c);
}

static void	init_maper(t_map *maper, int col, char **args)
{
	int	i;
	int	fd;

	maper->fl_map = 2;
	maper->fc_map = (col / 2) - (WIDTH_BOARD + 2);
	maper->actual_declared = false;
	maper->prev = -1;
	fd = open("/etc/vconsole.conf", O_RDONLY);
	if (fd == -1)
		maper->keyboard = 'q';
	else
		maper->keyboard = get_kb(fd);
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "-q") == 0 || !ft_strcmp(args[i], "--qwerty"))
			maper->keyboard = 'q';
		else if (!ft_strcmp(args[i], "-a") || !ft_strcmp(args[i], "--azerty"))
			maper->keyboard = 'a';
		i++;
	}
}

int	tetris(char **args)
{
	int				l;
	int				col;
	t_map			*maper;
	struct termios	old_term;

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
	init_maper(maper, col, args);
	draw_outside(maper);
	start_game(maper);
	tputs(tgoto(maper->cm_cap, 0, HEIGHT_BOARD + 4), 1, putchar);
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
	free(maper);
	printf("%s\n", WHITE);
	return (0);
}
