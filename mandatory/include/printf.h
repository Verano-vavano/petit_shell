/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:18:17 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/02 02:31:42 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct s_printf_flags
{
	bool	sharp;
	bool	zero;
	bool	minus;
	bool	space;
	bool	plus;
	int		field_length;
	int		accuracy;
	char	format;
}				t_printf_flags;

int				printf_loop(char **cmd, char *main_string);
bool			is_valid_format(char c, t_printf_flags *flags);

char			*modify_arg(char *arg, t_printf_flags flags, int *ret);
char			*convert_arg_to_format(char *arg, char format, int *ret);

char			*escape_characters(char *str);
t_printf_flags	get_printf_flags(char **s);

char			*sharp_it(char *arg, char format);
void			fill_array(char *s, char c, long size);
char			*make_it_bigger(char *arg, size_t len, size_t accuracy);
char			*add_pos(char *arg, char format, char *to_add);

#endif
