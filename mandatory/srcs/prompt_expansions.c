/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:41:40 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/09 16:34:40 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	*more_get_exp(char c, char *s, t_tool *tool, int *to_repl)
{
	char	username[2048];

	if (c == 'H')
		return (ft_strdup(get_hostname(username, tool->env)));
	else if (c == 'w' || c == 'W')
		return (get_arranged_cwd(tool->env, c == 'W'));
	else if (c == '\\')
		return (ft_strdup("\\"));
	else if (c == '$')
		return (ft_strdup("$"));
	else if (c == 'c')
		return (prompt_color(s + 2, to_repl));
	return (0);
}

static char	*get_exp_val(char c, char *s, t_tool *tool, int *to_repl)
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
	else
		return (more_get_exp(c, s, tool, to_repl));
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
	int		is_color;

	i = -1;
	while (ps[++i])
	{
		if (ps[i] != '\\')
			continue ;
		is_color = (ps[i + 1] == 'c');
		to_insert = get_exp_val(ps[i + 1], ps + i, tool, &is_color);
		if (to_insert)
			new = ft_strreplace(ps, i, 2 + is_color, to_insert);
		else
			new = ft_strreplace(ps, i, 1, "\\");
		if (new)
		{
			free(ps);
			ps = new;
		}
		if (to_insert)
			free(to_insert);
	}
	return (ps);
}
