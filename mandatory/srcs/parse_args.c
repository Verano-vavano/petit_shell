/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:58:21 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/05 14:23:01 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	duploop(char *s, char *arg, int i[4], char c)
{
	int	*dos;

	dos = &(i[3]);
	while (s[i[0]] && !is_separator(s[i[0]]))
	{
		if (is_metachar(s[i[0]]) && !is_delim(c))
			return (0);
		if (is_delim(s[i[0]]) && (i == 0 || s[i[0] - 1] != '\\')
			&& (c == s[i[0]] || !is_delim(c)))
		{
			arg[i[1]++] = s[i[0]];
			if (!is_delim(c) && s[i[0]] != ')' && s[i[0]] != '}')
				c = s[i[0]++];
			else if (c == s[i[0]++] && *dos == 0)
				c = ' ';
			else if (*dos == 1 && c == s[i[0] - 1])
				(*dos)--;
			c = convert_to_closing(c);
			continue ;
		}
		*dos = handle_parenthesis(&c, s[i[0]], *dos);
		arg[i[1]++] = s[i[0]++];
	}
	return (c);
}

char	rescue_funk(char *s, t_command *now_arg, int *i, char c)
{
	if (!s[i[0]] || !is_delim(c) || c == 0)
		return (0);
	while (s[i[0]] && is_separator(s[i[0]]))
	{
		if (now_arg)
			now_arg->content[i[1]++] = s[i[0]];
		i[0]++;
	}
	return (c);
}

static t_command	*init_duping(int i[3], t_command *args, char *s, int *meta)
{
	t_command	*now_arg;

	i[0] = 0;
	i[1] = 0;
	while (is_separator(s[i[0]]) && s[i[0]])
		i[0]++;
	*meta = is_metachar(s[i[0]]);
	i[2] = ft_strlen_arg(s + i[0], *meta);
	printf("%d\n", i[2]);
	now_arg = args;
	while (now_arg->next)
		now_arg = now_arg->next;
	now_arg->content = ft_calloc(i[2] + 1, sizeof (char));
	if (!now_arg->content)
		return (0);
	return (now_arg);
}

static int	ft_strdup_arg(char *s, t_command *args, char c)
{
	int			i[4];
	int			meta;
	t_command	*now_arg;

	now_arg = init_duping(i, args, s, &meta);
	if (!now_arg)
		return (-1);
	i[3] = 0;
	while (c)
	{
		if (!meta)
			c = duploop(s, now_arg->content, i, c);
		else
		{
			c = s[0];
			while (s[i[0]] && s[i[0]] == c)
				now_arg->content[i[1]++] = s[i[0]++];
		}
		c = rescue_funk(s, now_arg, i, c);
	}
	while (is_separator(s[i[0]]))
		i[0]++;
	if (s[i[0]] && s[i[0]] != '#')
		now_arg->next = init_command_arg(args);
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
	while (cmd[i] && cmd[i] != '#')
	{
		err_catcher = ft_strdup_arg(cmd + i, cmd_args, 's');
		if (err_catcher == -1)
			return (0);
		i += err_catcher;
	}
	return (cmd_args);
}
