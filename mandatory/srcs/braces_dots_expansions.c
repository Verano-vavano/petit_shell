/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_dots_expansions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:47:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/12 21:49:20 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static bool	is_in_bound(char c)
{
	return ((c >= 'A' && c <= 'z') || is_dgt(c));
}

static bool	dots_check(char **param)
{
	size_t	size0;
	size_t	size1;

	size0 = ft_strlen(param[0]);
	size1 = ft_strlen(param[1]);
	if (param[2][0] != 0 && !is_valid_num(param[2]))
		return (false);
	else if ((size0 != 1 && !is_valid_num(param[0]))
		|| (size1 != 1 && !is_valid_num(param[1])))
		return (false);
	else if ((size0 == 1 && !is_in_bound(param[0][0]))
		|| (size1 == 1 && !is_in_bound(param[1][0])))
		return (false);
	else if ((is_valid_num(param[0]) && !is_valid_num(param[1]))
		|| (is_valid_num(param[1]) && !is_valid_num(param[0])))
		return (false);
	return (true);
}

static char	**set_param(void)
{
	char	**param;
	int		i;

	param = ft_calloc(4, sizeof (char *));
	if (!param)
		return (0);
	i = 0;
	while (i < 3)
	{
		param[i] = ft_calloc(100, sizeof(char));
		if (!param[i])
		{
			free_char_etoile_etoile(param);
			return (0);
		}
		i++;
	}
	return (param);
}

static int	dots_loop(int *se, int *i, char *s, char **param)
{
	while (i[0] < se[1])
	{
		if (is_quoted(s, i[0], 0) || i[1] > 2)
			return (-1);
		if (s[i[0]] == '.' && s[i[0] + 1] != '.')
			return (-1);
		else if (s[i[0]] == '{')
			return (-2);
		else if (s[i[0]] == '.')
		{
			i[0] += 2;
			i[1]++;
			i[2] = 0;
			fill_char_etoile(param[i[1]], 0, 100);
			continue ;
		}
		else
			param[i[1]][i[2]] = s[i[0]];
		i[0]++;
		i[2]++;
	}
	return (0);
}

int	dots_brace_expansion(t_command *cmd, int *se)
{
	int		i[3];
	int		err;
	char	*s;
	char	**param;

	s = cmd->content;
	i[0] = se[0] + 1;
	i[1] = 0;
	i[2] = 0;
	param = set_param();
	if (!param)
		return (-1);
	err = dots_loop(se, i, s, param);
	if (err == -2)
	{
		free_char_etoile_etoile(param);
		return (-2);
	}
	if (err == -1 || (i[1] == 2 && param[2][0] == 0))
	{
		free_char_etoile_etoile(param);
		return (-1);
	}
	if (dots_check(param))
		return (dots_expansion(cmd, param, se));
	free_char_etoile_etoile(param);
	return (-1);
}
