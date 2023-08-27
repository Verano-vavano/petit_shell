/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:58:21 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/27 18:18:16 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

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

static int	ft_strdup_arg(char *cmd, t_command *cmd_args)
{
	int			len;
	int			i;
	int			total;
	t_command	*cmd_args_cpy;

	cmd_args_cpy = cmd_args;
	while (cmd_args_cpy->next)
		cmd_args_cpy = cmd_args_cpy->next;
	total = 0;
	while (cmd[total] && is_separator(cmd[total]))
		total++;
	cmd = cmd + total;
	len = ft_strlen_arg(cmd, is_metachar(cmd[0]));
	total += len;
	cmd_args_cpy->content = ft_calloc(len + 1, sizeof (char));
	i = -1;
	while (++i < len)
		cmd_args_cpy->content[i] = cmd[i];
	printf("%s\n", cmd_args_cpy->content);
	while (cmd[total] && is_separator(cmd[total]))
		total++;
	if (cmd[total] && cmd[total] != '#')
		cmd_args_cpy->next = init_command_arg(cmd_args);
	return (total);
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
		err_catcher = ft_strdup_arg(cmd + i, cmd_args);
		if (err_catcher == -1)
			return (0);
		i += err_catcher;
	}
	return (cmd_args);
}
