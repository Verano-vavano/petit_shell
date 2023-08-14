/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_dots_expansions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:47:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/14 08:01:15 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	dots_expansion(t_command *cmd, char **param)
{
	long		l_params[3];
	bool		way;
	bool		moved;
	bool		charer;
	t_command	*temp;

	l_params[2] = 1;
	if (param[2][0] != 0)
		l_params[2] = ft_atol(param[2]);
	if (l_params[2] == 0)
		l_params[2] = 1;
	l_params[2] = ((l_params[2] * (-1) * (l_params[2] < 0)) + (l_params[2] * (l_params[2] > 0)));
	charer = false;
	if (!is_valid_num(param[0]) && param[0][0] != '-' && param[0][0] != '+')
	{
		charer = true;
		l_params[0] = param[0][0];
	}
	else
		l_params[0] = ft_atol(param[0]);
	if (charer)
		l_params[1] = param[1][0];
	else
		l_params[1] = ft_atol(param[1]);
	way = (l_params[0] < l_params[1]);
	moved = false;
	while ((way && l_params[0] <= l_params[1]) || (!way && l_params[0] >= l_params[1]))
	{
		if (!moved)
		{
			free(cmd->content);
			if (!charer)
				cmd->content = ft_ltoa(l_params[0]);
			else
			{
				cmd->content = ft_calloc(2, sizeof (char));
				cmd->content[0] = l_params[0];
			}
			moved = true;
		}
		else
		{
			temp = ft_calloc(1, sizeof (t_command));
			if (!temp)
				return (-1);
			temp->next = cmd->next;
			if (!charer)
				temp->content = ft_ltoa(l_params[0]);
			else
			{
				temp->content = ft_calloc(2, sizeof (char));
				temp->content[0] = l_params[0];
			}
			temp->purpose = COMMAND;
			cmd->next = temp;
			cmd = cmd->next;
		}
		l_params[0] += ((way * l_params[2]) + (!way * l_params[2] * (-1)));
	}
	return (0);
}

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
	if (param[2][0] != 0 && !is_all_num(param[2]))
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

	param = ft_calloc(3, sizeof (char *));
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

int	dots_brace_expansion(t_command *cmd, int *se)
{
	int		i[3];
	char	*s;
	char	**param;

	s = cmd->content;
	i[0] = se[0] + 1;
	i[1] = 0;
	i[2] = 0;
	param = set_param();
	if (!param)
		return (-1);
	while (i[0] < se[1])
	{
		if (is_quoted(s, i[0], 0) || i[1] > 2)
			return (-1);
		if (s[i[0]] == '.' && s[i[0] + 1] != '.')
			return (-1);
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
	if (i[1] == 2 && param[2][0] == 0)
		return (-1);
	if (dots_check(param))
		return (dots_expansion(cmd, param));
	return (-1);
}
