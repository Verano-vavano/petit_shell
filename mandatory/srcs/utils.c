/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:17:54 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/13 11:10:08 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

t_command	*init_command_arg(t_command *start)
{
	t_command	*new_arg;

	new_arg = ft_calloc(1, sizeof (t_command));
	if (!new_arg)
	{
		free_command(start);
		return (0);
	}
	return (new_arg);
}

bool	is_dir(char *path)
{
	struct stat	file_stat;

	if (lstat(path, &file_stat) == 0)
		return (S_ISDIR(file_stat.st_mode));
	return (false);
}

int	usearch(char *s, char c)
{
	char	quoted;
	int		i;

	quoted = 0;
	i = 0;
	while (s[i])
	{
		quoted = is_quoted(s, i, quoted);
		if (s[i] == c && !quoted)
			return (i);
		i++;
	}
	return (i);
}

bool	is_file_valid(char *file, int mode)
{
	return (access(file, mode) == 0);
}

bool	is_valid_var_char(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == '_');
}
