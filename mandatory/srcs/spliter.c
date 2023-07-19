/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:43:04 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/18 11:51:07 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	not_ended(char *s)
{
	int		dos;
	int		i;
	char	c;

	c = 's';
	i = 0;
	dos = 0;
	while (s[i])
	{
		if (is_delim(s[i]) && (i == 0 || s[i - 1] != '\\')
			&& (c == s[i] || !is_delim(c)))
		{
			if (!is_delim(c) && s[i] != ')' && s[i] != '}')
				c = s[i];
			else if (c == s[i] && !dos)
				c = ' ';
			else if (dos && c == s[i])
				dos--;
			c = convert_to_closing(c);
		}
		dos = handle_parenthesis(&c, s[i], dos);
		i++;
	}
	return ((is_delim(c) && c != ')' && c != '}') || dos);
}

static int	check_ender(char *line)
{
	int		i;
	char	c;

	i = 0;
	c = 'L';
	while (line[i])
	{
		if (line[i] == '|')
			c = '|';
		if (line[i + 1] == 0 && line[i] == '\\')
			return (1);
		else if (c == '|' && !is_separator(line[i]))
			c = 'L';
		i++;
	}
	return (c != 'L');
}

static char	*new_line_add(char *line)
{
	char	*new_line;
	char	*joined;

	new_line = 0;
	while (!new_line || !(*new_line))
		new_line = readline(PS2);
	joined = ft_strjoin(line, "\n");
	free(line);
	line = ft_strjoin(joined, new_line);
	free(new_line);
	free(joined);
	return (line);
}

t_command	*spliter_init(char *line)
{
	t_command		*cmd;
	char			where_did_we_fail;

	while (1)
	{
		if (check_syntax(line))
		{
			add_history(line);
			free(line);
			return (0);
		}
		where_did_we_fail = (not_ended(line) || check_ender(line));
		if (!where_did_we_fail)
			break ;
		line = new_line_add(line);
	}
	cmd = ft_split_cmd(line);
	add_history(line);
	free(line);
	return (cmd);
}
