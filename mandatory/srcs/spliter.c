/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:43:04 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/25 20:28:23 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

// I ain't scared of no norm
static int	not_ended(char *s)
{
	int		i;
	char	q;
	int		par;
	bool	backslashed;
	bool	m;

	i = -1;
	q = 0;
	par = 0;
	backslashed = false;
	m = false;
	while (s[++i])
	{
		if (s[i] == q && !backslashed)
			q = 0;
		else if ((s[i] == '(' || s[i] == ')') && !q && !backslashed)
			par += (1 * (s[i] == '(')) + (-1 * (s[i] == ')'));
		else if (!q && (s[i] == '\'' || s[i] == '"') && !backslashed)
			q = s[i];
		backslashed = (s[i] == '\\' && !backslashed);
		m = (!q && (s[i] == '&' || s[i] == '|' || (m && is_separator(s[i]))));
	}
	return (backslashed || q || par || m);
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

	signal(SIGINT, sig_main);
	signal(SIGQUIT, sig_main);
	new_line = new_prompt(2, tool);
	signal(SIGINT, sig_catch);
	signal(SIGQUIT, sig_catch);
	if (!new_line)
		printfd(STDERR_FILENO, "syntax error: unexpected EOF\n");
	if (nl)
	{
		joined = ft_strjoin(line, "\n");
		free(line);
	}
	else
		joined = line;
	if (!joined || !new_line)
		return (0);
	line = ft_strjoin(joined, new_line);
	free(new_line);
	free(joined);
	return (line);
}

t_command	*spliter_init(char **line, bool add_line, t_tool *tool)
{
	t_command		*cmd;
	char			where_did_we_fail;

	while (line && *line && **line)
	{
		if (check_syntax(*line))
		{
			if (add_line)
				add_to_hist(tool->env, tool->hist, *line);
			return (0);
		}
		where_did_we_fail = not_ended(*line);
		if (where_did_we_fail == -1)
			(*line)[ft_strlen(*line) - 1] = '\0';
		if (!where_did_we_fail && !check_ender(*line))
			break ;
		*line = new_line_add(*line, where_did_we_fail != -1, tool);
	}
	if (!(*line))
		return (0);
	cmd = ft_split_cmd(*line);
	if (add_line)
		add_to_hist(tool->env, tool->hist, *line);
	return (cmd);
}
