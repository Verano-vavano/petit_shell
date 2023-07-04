/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:05:46 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/04 11:19:34 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	dup_loop(char *s, char *arg, int *i, char c)
{
	while (s[i[0]] && !is_separator(s[i[0]]))
	{
		if (is_metachar(s[i[0]]) && !is_delim(c))
			return (0);
		if (is_delim(s[i[0]]) && (s[i[0] - 1] != '\\')
			&& (c == s[i[0]] || !is_delim(c)))
		{
			arg[i[1]++] = s[i[0]];
			if (!is_delim(c))
				c = s[i[0]++];
			else if (c == s[i[0]++])
				c = ' ';
			continue ;
		}
		arg[i[1]++] = s[i[0]++];
	}
	return (c);
}

static int	ft_strdup_arg(char *s, t_command *args)
{
	int			i[3];
	char		c;
	int			meta;
	t_command	*now_arg;

	i[0] = 0;
	i[1] = 0;
	while (is_separator(s[i[0]]) && s[i[0]])
		i[0]++;
	meta = is_metachar(s[i[0]]);
	i[2] = ft_strlen_arg(s + i[0], meta);
	now_arg = args;
	while (now_arg->next)
		now_arg = now_arg->next;
	now_arg->content = ft_calloc(i[2] + 1, sizeof (char));
	if (!now_arg->content)
		return (-1);
	c = 's';
	while (c)
	{
		if (!meta)
			c = dup_loop(s, now_arg->content, i, c);
		else
		{
			c = s[0];
			while (s[i[0]] && s[i[0]] == c)
			{
				now_arg->content[i[1]++] = c;
				i[0]++;
			}
		}
		if (!s[i[0]] || !is_delim(c) || c == 0)
			break ;
		while (s[i[0]] && is_separator(s[i[0]]))
		{
			now_arg->content[i[1]++] = ' ';
			i[0]++;
		}
	}
	while (is_separator(s[i[0]]))
		i[0]++;
	if (s[i[0]] && s[i[0]] != '#')
		now_arg->next = init_command_arg(args);
	return (i[0]);
}

t_command	*ft_split_cmd(char *cmd, t_command *cmd_args)
{
	int			i;
	int			j;
	int			err_catcher;

	i = 0;
	j = 0;
	if (!cmd[i])
		return (0);
	if (!cmd_args)
		cmd_args = ft_calloc(1, sizeof (t_command));
	else
	{
		cmd_args->next = ft_calloc(1, sizeof (t_command));
		cmd_args = cmd_args->next;
	}
	i = 0;
	while (cmd[i] && is_separator(cmd[i]))
		i++;
	while (cmd[i] && cmd[i] != '#')
	{
		err_catcher = ft_strdup_arg(cmd + i, cmd_args);
		if (err_catcher == -1)
			return (0);
		i += err_catcher;
	}
	return (cmd_args);
}
