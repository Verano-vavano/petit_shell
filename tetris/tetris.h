/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:58:47 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/09 17:55:18 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRIS_H
# define TETRIS_H

# define SQUARE "██"
# define WIDTH_BOARD 12
# define HEIGHT_BOARD 22
# define MAX_LEVEL 5

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

# define I_COLOR RED
# define O_COLOR CYAN
# define T_COLOR PURPLE
# define L_COLOR GREEN
# define J_COLOR BLUE
# define S_COLOR RED
# define Z_COLOR YELLOW

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <sys/wait.h>
# include <time.h>
# include <sys/syscall.h>
# include <limits.h>
# include "../libft/libft.h"

enum	e_piece
{
	I_PIECE,
	O_PIECE,
	T_PIECE,
	L_PIECE,
	J_PIECE,
	S_PIECE,
	Z_PIECE
};

enum	e_way
{
	DOWN,
	LEFT,
	RIGHT
};

typedef struct s_map
{
	char			*cm_cap;
	int				fl_map;
	int				fc_map;
	bool			actual_declared;
	char			actual[4][4];
	char			next[4][4];
	int				prev;
	int				fl_next;
	int				fc_next;
	char			**map;
	int				x_pivot;
	int				y_pivot;
	unsigned long	score;
	int				lines_destroyed;
	int				level;
}				t_map;

void	start_game(t_map *map);
void	draw_outside(t_map *map);
int		move_piece(t_map *map);
int		add_piece(t_map *map);
void	cpy_piece(t_map *map);
void	get_next_piece(t_map *map);
void	draw_next(t_map *map);
pid_t	sleepy_time(int level);
void	perform_move(t_map *map, char c);
void	line_checker(t_map *map);
void	swap_lines(char *l1, char *l2);
void	empty_line(char *line);
bool	is_line_full(char *line);
bool	line_not_zero(char *map);
void	hard_drop_score(t_map *map, int y_start);
int		soft_drop_score(t_map *map, bool return_it);
void	update_score(t_map *map, int l);
void	update_level(t_map *map, int l);
char	**create_temp_arr(void);

bool	verif_down(t_map *map);
void	move_down(t_map *map);
void	hard_drop(t_map *map);
bool	verif_side(t_map *map, char side);
void	move_side(t_map *map, char side);
bool	verif_rotate(t_map *map, char side);
void	rotate_side(t_map *map, char side);

void	draw_piece(t_map *map, char *color);
void	replace_moving(t_map *map);

char	get_char_map(char s[4][4]);
void	change_color(char color);

void	i_form(t_map *map);
void	o_form(t_map *map);
void	t_form(t_map *map);
void	l_form(t_map *map, int n);
void	s_form(t_map *map, int n);

void	fill_char_etoile(char *s, char c, int len);
void	free_char_etoile_etoile(char **truc);
void	print_map(char **map);
void	*ft_calloc(size_t count, size_t size);
time_t	ft_time(void);
long	ft_getpid(void);
int		ft_random(void);
int		ft_randint(int low, int high);
int		ft_tolower(int c);
bool	ft_isupper(char c);
int		ft_strchr_int(const char *s, int c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_simple_ftoa(float f, int dec);

#endif
