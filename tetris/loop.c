/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:33:34 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/10 15:03:41 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetris.h"
#include "../mandatory/include/sig.h"

static void	sig_received(int sig)
{
	g_sig_rec = sig;
}

static char	**get_map(void)
{
	char	**map;
	int		i;

	map = ft_calloc(HEIGHT_BOARD + 3, sizeof (char *));
	if (map == 0)
		return (0);
	i = 0;
	while (i < HEIGHT_BOARD + 2)
	{
		map[i] = ft_calloc(WIDTH_BOARD + 3, sizeof (char));
		if (map[i] == 0)
		{
			free_char_etoile_etoile(map);
			return (0);
		}
		if (i == 0 || i == HEIGHT_BOARD + 1)
			fill_char_etoile(map[i], '1', WIDTH_BOARD + 2);
		else
			fill_char_etoile(map[i], '0', WIDTH_BOARD + 2);
		map[i][0] = '1';
		map[i][WIDTH_BOARD + 1] = '1';
		i++;
	}
	return (map);
}

static void	game_loop(t_map *map)
{
	char	c[1];
	pid_t	pid;

	pid = -1;
	c[0] = 0;
	while (!g_sig_rec)
	{
		if (c[0] == 'p')
			break ;
		if (c[0])
			perform_move(map, c[0]);
		if (pid != -1 && waitpid(pid, 0, WNOHANG) != 0)
		{
			if (move_piece(map))
				break ;
			pid = -1;
		}
		if (pid == -1)
			pid = sleepy_time(map->level);
		if (c[0])
			c[0] = 0;
		read(STDIN_FILENO, c, 1);
	}
}

void	start_game(t_map *map)
{
	signal(SIGINT, sig_received);
	signal(SIGQUIT, sig_received);
	map->score = 0;
	map->lines_destroyed = 0;
	map->level = 0;
	map->map = get_map();
	if (map->map == 0)
		return ;
	game_loop(map);
	free_char_etoile_etoile(map->map);
}
