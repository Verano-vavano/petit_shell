/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:43:04 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/19 17:33:47 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	not_ended(char *s)
{
	int		i;
	char	quoted;
	int		par;
	bool	backslashed;
	bool	s_meta;

	i = 0;
	quoted = 0;
	par = 0;
	backslashed = false;
	s_meta = false;
	while (s[i])
	{
		if (s[i] == quoted && !backslashed)
			quoted = 0;
		else if (s[i] == '\\' && !backslashed)
			backslashed = true;
		else if (s[i] == '(' && !quoted && !backslashed)
			par++;
		else if (s[i] == ')' && !quoted && !backslashed)
			par--;
		else if (backslashed)
			backslashed = false;
		else if (!quoted && (s[i] == '\'' || s[i] == '"'))
			quoted = s[i];
		s_meta = (!quoted && (s[i] == '&' || s[i] == '|'
					|| (s_meta && is_separator(s[i]))));
		i++;
	}
	return (backslashed || quoted || par || s_meta);
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
	signal(SIGINT, sig_main);
	signal(SIGQUIT, sig_main);
	new_line = new_prompt(2, tool);
	signal(SIGINT, sig_catch);
	signal(SIGQUIT, sig_catch);
	if (!new_line)
	{
		printfd(STDERR_FILENO, "syntax error: unexpected EOF\n");
		return (0);
	}
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
