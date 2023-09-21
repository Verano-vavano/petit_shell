/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:41:40 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/21 13:37:14 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	*change_bold_color(char c)
{
	if (c == 'N')
		return (ft_strdup(BLACK_BOLD));
	else if (c == 'R')
		return (ft_strdup(RED_BOLD));
	else if (c == 'G')
		return (ft_strdup(GREEN_BOLD));
	else if (c == 'Y')
		return (ft_strdup(YELLOW_BOLD));
	else if (c == 'B')
		return (ft_strdup(BLUE_BOLD));
	else if (c == 'P')
		return (ft_strdup(PURPLE_BOLD));
	else if (c == 'C')
		return (ft_strdup(CYAN_BOLD));
	else
		return (ft_strdup(WHITE_BOLD));
}

static char	*change_color(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (change_bold_color(c));
	else if (c == 'n')
		return (ft_strdup(BLACK));
	else if (c == 'r')
		return (ft_strdup(RED));
	else if (c == 'g')
		return (ft_strdup(GREEN));
	else if (c == 'y')
		return (ft_strdup(YELLOW));
	else if (c == 'b')
		return (ft_strdup(BLUE));
	else if (c == 'p')
		return (ft_strdup(PURPLE));
	else if (c == 'c')
		return (ft_strdup(CYAN));
	else
		return (ft_strdup(WHITE));
}

static char	*get_exp_val(char c, char next, t_tool *tool)
{
	char	username[2048];

	if (c == 'a')
		return (ft_strdup("\a"));
	else if (c == 'n')
		return (ft_strdup("\n"));
	else if (c == 'r')
		return (ft_strdup("\r"));
	else if (c == 's')
		return (ft_strdup(SHELL_NAME));
	else if (c == 'v')
		return (ft_strdup(SHELL_VERSION));
	else if (c == 'u')
		return (ft_strdup(get_username(username, tool->env)));
	else if (c == '#')
	{
		if (tool->hist->hist_end->num_cmd == LONG_MAX)
			return (ft_ltoa(LONG_MAX));
		return (ft_ltoa(tool->hist->hist_end->num_cmd + 1));
	}
	else if (c == 'H')
		return (ft_strdup(get_hostname(username, tool->env)));
	else if (c == 'w' || c == 'W')
		return (get_arranged_cwd(tool->env, c == 'W'));
	else if (c == '\\')
		return (ft_strdup("\\"));
	else if (c == 'c')
		return (change_color(next));
	return (0);
}

/*	PS_EXPANSION applied to PS0, 1 and 2 !
 *	\a : rings a bell
 *	\H : hostname
 *	\n : newline
 *	\r : carriage return
 *	\s : Shell name
 *	\u : username
 *	\v : Shell version
 *	\w : pwd from / or ~
 *	\W : cwd
 *	\# : command number
 *	\cC : sets color as C
 *	\\ : \
 * */
char	*ps_cool_expansion(char *ps, t_tool *tool)
{
	int		i;
	char	*to_insert;
	char	*new;
	bool	is_color;

	i = -1;
	while (ps[++i])
	{
		if (ps[i] == '\\')
		{
			is_color = (ps[i + 1] == 'c');
			if (is_color)
				to_insert = get_exp_val(ps[i + 1], ps[i + 2], tool);
			else
				to_insert = get_exp_val(ps[i + 1], 0, tool);
			if (to_insert)
			{
				new = ft_strreplace(ps, i, 2 + is_color, to_insert);
				free(to_insert);
			}
			else
				new = ft_strreplace(ps, i, 1, "\\");
			if (new)
			{
				free(ps);
				ps = new;
			}
		}
	}
	return (ps);
}
