/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_dots_expansions_more.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:48:22 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/18 18:49:05 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	*get_content(long arg, char **s, bool is_num)
{
	char	*temp;
	char	*temp2;
	char	*mid;

	if (is_num)
	{
		mid = ft_calloc(2, sizeof(char));
		if (mid)
			mid[0] = arg;
	}
	else
		mid = ft_ltoa(arg);
	if (!mid)
		return (0);
	temp = ft_strjoin(s[0], mid);
	free(mid);
	if (!temp)
		return (0);
	temp2 = ft_strjoin(temp, s[1]);
	return (temp2);
}

static t_command	*change_val(t_command *cmd, bool moved, char *to_put)
{
	t_command	*temp;

	if (!to_put)
		return (0);
	if (!moved)
	{
		free(cmd->content);
		cmd->content = to_put;
		moved = true;
	}
	else
	{
		temp = ft_calloc(1, sizeof (t_command));
		if (!temp)
			return (0);
		temp->next = cmd->next;
		temp->content = to_put;
		temp->purpose = COMMAND;
		cmd->next = temp;
		cmd = cmd->next;
	}
	return (cmd);
}

static char	**get_delims(t_command *cmd, int *se)
{
	char	**strs;

	strs = ft_calloc(2, sizeof (char *));
	if (!strs)
		return (0);
	strs[0] = ft_strndup(cmd->content, ft_strchr_int(cmd->content, '{'));
	if (!strs[0])
	{
		free(strs);
		return (0);
	}
	strs[1] = ft_strdup(cmd->content + se[1] + 1);
	if (!strs[1])
	{
		free(strs[0]);
		free(strs);
		return (0);
	}
	return (strs);
}

static int	add_it_all(t_command *cmd, long *l_p, int *se, bool charer)
{
	char	**strs;
	char	*to_put;
	bool	moved;
	bool	way;

	way = (l_p[0] <= l_p[1]);
	strs = get_delims(cmd, se);
	if (!strs)
		return (0);
	moved = false;
	while ((way && l_p[0] <= l_p[1]) || (!way && l_p[0] >= l_p[1]))
	{
		to_put = get_content(l_p[0], strs, charer);
		cmd = change_val(cmd, moved, to_put);
		if (!to_put)
			break ;
		moved = true;
		l_p[0] += ((way * l_p[2]) + (!way * l_p[2] * (-1)));
	}
	free(strs[0]);
	free(strs[1]);
	free(strs);
	return (0);
}

int	dots_expansion(t_command *cmd, char **param, int *se)
{
	long		l_p[3];
	bool		charer;

	l_p[2] = 1;
	if (param[2][0] != 0)
		l_p[2] = ft_atol(param[2]);
	if (l_p[2] == 0)
		l_p[2] = 1;
	l_p[2] = ((l_p[2] * (-1) * (l_p[2] < 0)) + (l_p[2] * (l_p[2] > 0)));
	charer = false;
	if (!is_valid_num(param[0]) && param[0][0] != '-' && param[0][0] != '+')
	{
		charer = true;
		l_p[0] = param[0][0];
	}
	else
		l_p[0] = ft_atol(param[0]);
	if (charer)
		l_p[1] = param[1][0];
	else
		l_p[1] = ft_atol(param[1]);
	return (add_it_all(cmd, l_p, se, charer));
}
