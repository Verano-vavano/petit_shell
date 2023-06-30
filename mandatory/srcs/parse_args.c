/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:05:46 by hdupire           #+#    #+#             */
/*   Updated: 2023/06/30 11:51:51 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	dup_loop(char *s, char *arg, int *i, char c)
{
	while (s[i[0]] && !is_separator(s[i[0]]))
	{
		if (is_metachar(s[i[0]]) && !is_delim(c) && c != 's')
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
	t_command	*now_arg;

	i[0] = 0;
	i[1] = 0;
	while (is_separator(s[i[0]]) && s[i[0]])
		i[0]++;
	i[2] = ft_strlen_arg(s + i[0]);
	printf("%d\n", i[2]);
	now_arg = args;
	while (now_arg->next)
		now_arg = now_arg->next;
	now_arg->content = ft_calloc(i[2] + 1, sizeof (char));
	if (!now_arg->content)
		return (-1);
	c = 's';
	while (c)
	{
		c = dup_loop(s, now_arg->content, i, c);
		if (!s[i[0]] || !is_delim(c) || c == 0)
			break ;
		while (s[i[0]] && is_separator(s[i[0]]))
		{
			now_arg->content[i[1]++] = ' ';
			i[0]++;
		}
	}
	if (s[i[0]])
		now_arg->next = init_command_arg(args);
	printf("%s\n", now_arg->content);
	return (i[0]);
}

t_command	*ft_split_cmd(char *cmd)
{
	int			i;
	int			err_catcher;
	t_command	*cmd_args;

	i = 0;
	if (!cmd[i])
		return (0);
	cmd_args = ft_calloc(1, sizeof (t_command));
	i = 0;
	while (cmd[i] && is_separator(cmd[i]))
		i++;
	while (cmd[i])
	{
		err_catcher = ft_strdup_arg(cmd + i, cmd_args);
		if (err_catcher == -1)
			return (0);
		i += err_catcher;
	}
	return (cmd_args);
}
