/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:43:04 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/14 18:39:10 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	not_ended(char *s)
{
	int		dos;
	int		i;
	char	c;

	c = 's';
	i = -1;
	dos = 0;
	while (s[++i])
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
	}
	if (!is_delim(c) && i > 0 && s[i - 1] == '\\')
		return (-1);
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
		if (!line[i + 1] && line[i] == '\\')
			return (1);
		else if (c == '|' && !is_separator(line[i]))
			c = 'L';
		i++;
	}
	return (c != 'L');
}

static char	*new_line_add(char *line, bool nl, t_tool *tool)
{
	char	*new_line;
	char	*joined;

	new_line = NULL;
	while (!new_line || !(*new_line))
		new_line = new_prompt(2, tool);
	if (nl)
	{
		joined = ft_strjoin(line, "\n");
		free(line);
		if (!joined)
			return (0);
	}
	else
		joined = line;
	line = ft_strjoin(joined, new_line);
	free(new_line);
	free(joined);
	return (line);
}

t_command	*spliter_init(char *line, bool add_line, t_tool *tool)
{
	t_command		*cmd;
	char			where_did_we_fail;

	while (line && *line)
	{
		if (check_syntax(line))
		{
			if (add_line)
				add_to_hist(tool->env, tool->hist, line);
			return (0);
		}
		where_did_we_fail = not_ended(line);
		if (where_did_we_fail == -1)
			line[ft_strlen(line) - 1] = '\0';
		if (!where_did_we_fail && !check_ender(line))
			break ;
		line = new_line_add(line, where_did_we_fail != -1, tool);
	}
	if (!line)
		return (0);
	cmd = ft_split_cmd(line);
	if (add_line)
		add_to_hist(tool->env, tool->hist, line);
	return (cmd);
}
