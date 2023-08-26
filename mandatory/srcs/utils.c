/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:17:54 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/26 11:46:45 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

t_command	*init_command_arg(t_command *start)
{
	t_command	*new_arg;

	new_arg = ft_calloc(1, sizeof (t_command));
	if (new_arg == 0)
	{
		free_command(start);
		return (0);
	}
	return (new_arg);
}

bool	is_dir(char *path)
{
	struct stat	fileStat;

	if (lstat(path, &fileStat) == 0)
		return (S_ISDIR(fileStat.st_mode));
	return (false);
}

int	unquote_search(char *s, char c)
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
