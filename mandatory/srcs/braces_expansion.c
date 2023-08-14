/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:01:48 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/14 20:24:57 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	brace_expand_it(t_command *cmd, int start, int end, bool inner);
int	find_closing_brack(char *s);

static int	find_end(char *s)
{
	int	i;

	i = 0;
	printf("START END IS : %s\n", s);
	while (s[i] && s[i] != ',' && s[i] != '}')
		i++;
	return (i);
}

static char	*get_braces_ext(int *se, int *nodes, char *org)
{
	char	*temp;
	char	*temp2;
	char	*temp3;

	temp = ft_strndup(org + se[2], ft_strchr_int(org + se[2], '{'));
	if (!temp)
		return (0);
	printf("START = %s\n", temp);
	temp2 = ft_strndup(org + nodes[1] + 1, nodes[0] - nodes[1] - 1);
	if (!temp2)
	{
		free(temp);
		return (0);
	}
	printf("MIDDLE = %s\n", temp2);
	temp3 = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	if (!temp3)
		return (0);
	if (se[3] != -1)
	{
		temp2 = ft_strndup(org + se[1] + 1, find_end(org + se[1] + 1));
		if (!temp2)
			return (temp3);
		temp = ft_strjoin(temp3, temp2);
		free(temp2);
	}
	else
		temp = ft_strjoin(temp3, org + se[1] + find_end(org + se[1]) + 1);
	free(temp3);
	return (temp);
}

static char	*add_to_str(int *se, int *nodes, char *org, char *repl)
{
	char	*temp;
	char	*temp2;

	temp = get_braces_ext(se, nodes, org);
	printf("--We're in %s\n\n", temp);
	if (!temp)
		return (0);
	if (!repl)
		return (temp);
	temp2 = ft_strjoin(repl, ",");
	if (!temp2)
	{
		free(temp);
		return (0);
	}
	free(repl);
	repl = ft_strjoin(temp2, temp);
	free(temp);
	free(temp2);
	return (repl);
}

static void	add_to_chain(t_command *cmd, int *se, int *nodes, char *org)
{
	char	*temp;
	t_command	*new_cmd;
	int		repl_index;

	repl_index = nodes[2];
	if (repl_index)
	{
		while (repl_index != 1)
		{
			cmd = cmd->next;
			repl_index--;
		}
		new_cmd = ft_calloc(1, sizeof (t_command));
		new_cmd->purpose = COMMAND;
		if (cmd->next)
			new_cmd->next = cmd->next;
		cmd->next = new_cmd;
		cmd = cmd->next;
	}
	temp = get_braces_ext(se, nodes, org);
	if (temp)
	{
		free(cmd->content);
		cmd->content = temp;
	}
}

static int	coma_brace_expansion(t_command *cmd, int *start_end, bool inner)
{
	char	*org;
	char	*repl;
	char	quoted;
	int		nodes[3];

	org = ft_strdup(cmd->content);
	if (!org)
		return (1);
	quoted = 0;
	nodes[0] = start_end[0];
	nodes[1] = start_end[0];
	nodes[2] = 0;
	repl = 0;
	while (org[nodes[0]] && !(org[nodes[0]] == '}' && org[nodes[0] - 1] != '\\'))
	{
		quoted = is_quoted(org, nodes[0], quoted);
		if (!quoted && org[nodes[0]] == ',' && org[nodes[0] - 1] != '\\')
		{
			if (!inner)
				add_to_chain(cmd, start_end, nodes, org);
			else
				repl = add_to_str(start_end, nodes, org, repl);
			nodes[2]++;
			nodes[1] = nodes[0];
		}
		nodes[0]++;
	}
	if (!inner)
		add_to_chain(cmd, start_end, nodes, org);
	else
	{
		repl = add_to_str(start_end, nodes, org, repl);
		printf("START REPLACE = %s\n", cmd->content + start_end[2]);
		printf("START RESEARCH = %s\n", cmd->content + start_end[1] + 1);
		printf("WILL REMOVE %d\n", find_closing_brack(cmd->content + start_end[2] + ft_strchr_int(cmd->content + start_end[2], '{')) + find_end(cmd->content + start_end[1] + 1) + 2);
		printf("BECAUSE CLOS_BRACK = %d && END = %d\n", find_closing_brack(cmd->content + start_end[2] + ft_strchr_int(cmd->content + start_end[2], '{')), find_end(cmd->content + start_end[3] + 1));
		printf("SE[0] = %s\n", cmd->content + start_end[0]);
		printf("SE[1] = %s\n", cmd->content + start_end[1]);
		printf("SE[2] = %s\n", cmd->content + start_end[2]);
		printf("SE[3] = %s\n", cmd->content + start_end[3]);
		printf("nodes[0] = %s\n", cmd->content + nodes[0]);
		printf("nodes[1] = %s\n", cmd->content + nodes[1]);
		printf("nodes[2] = %s\n", cmd->content + nodes[2]);
		cmd->content = ft_strreplace(cmd->content, start_end[2], find_closing_brack(cmd->content + start_end[2] + ft_strchr_int(cmd->content + start_end[2], '{')) + find_end(cmd->content + start_end[3] + 1) + 1, repl);
		printf("AND NOW ITS : %s\n", cmd->content);
	}
	return (0);
}

static int	apply_brace_exp(t_command *cmd, int *indeces, bool inner)
{
	int		index;
	char	*s;
	char	quoted;

	s = cmd->content;
	quoted = 0;
	index = indeces[0];
	brace_expand_it(cmd, indeces[0] + 1, indeces[1], true);
	while (s[index])
	{
		quoted = is_quoted(cmd->content, index, quoted);
		if (!quoted && s[index] == ',' && s[index - 1] != '\\')
		{
			return (coma_brace_expansion(cmd, indeces, inner));
		}
		index++;
	}
	return (dots_brace_expansion(cmd, indeces));
}

int	find_closing_brack(char *s)
{
	int	quoted;
	int	i;

	i = 0;
	quoted = 0;
	printf("TO FIND CLOSE : %s\n", s);
	while (s[i])
	{
		quoted = is_quoted(s, i, quoted);
		if (s[i] == '}' && !quoted && s[i - 1] != '\\')
			return (i);
		i++;
	}
	return (-1);
}

static int	check_brace_exp(char *s)
{
	int		quoted;
	bool	doable;
	int		i;

	i = 1;
	quoted = 0;
	doable = false;
	while (s[i])
	{
		quoted = is_quoted(s, i, quoted);
		if (!quoted && (s[i] == ',' || (s[i] == '.' && s[i + 1] == '.')))
			doable = true;
		if (s[i] == '{' && !quoted && s[i - 1] != '\\')
		{
			i += find_closing_brack(s + i) + 1;
			if (i == -1)
				return (0);
		}
		if (s[i] == '}' && !quoted && doable && s[i - 1] != '\\')
			return (i);
		i++;
	}
	return (0);
}

int	brace_expand_it(t_command *cmd, int start, int end, bool inner)
{
	bool	expanded;
	int		quoted;
	int		i;
	int		indeces[4];

	i = start;
	quoted = 0;
	expanded = false;
	indeces[2] = start;
	indeces[3] = end;
	printf("LOL %d : %s\n", inner, cmd->content);
	while (cmd->content[i] && (end == -1 || i < end))
	{
		quoted = is_quoted(cmd->content, i, quoted);
		if (cmd->content[i] == ',')
			indeces[2] = i + 1;
		if (cmd->content[i] == '{' && (i == 0 || (cmd->content[i - 1] != '$'
			&& cmd->content[i - 1] != '\\')) && !quoted)
		{
			indeces[1] = i + check_brace_exp(cmd->content + i);
			if (indeces[1] != i)
			{
				if (cmd->purpose >= IN_FILE && cmd->purpose <= HERE_STRING)
					return (some_error(cmd->content, "ambiguous redirect"));
				indeces[0] = i;
				i = apply_brace_exp(cmd, indeces, inner);
				printf("I is %d\n", i);
				if (i < 0)
					return (1);
				expanded = true;
				break ;
			}
		}
		i++;
	}
	if (expanded)
		brace_expand_it(cmd, start, end, inner);
	return (0);
}

/* Expansions of sort l{o,a,i}l and l{0..5..2}
 * l{o,a,i}l -> lol lal lil
 * l{0..5..2} -> 0 2 4
 * also manages ambiguous redirects such as >{l,o} and bad substitutions 
 * inner brackets arent functionning as bash, ill see later */
int	braces_expansion(t_command *cmd)
{
	int	err_man;

	signal(SIGINT, SIG_DFL);
	err_man = 0;
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		if (ft_strchr(cmd->content, '{') && ft_strchr(cmd->content, '}'))
			err_man = brace_expand_it(cmd, 0, -1, false);
		if (err_man)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}
