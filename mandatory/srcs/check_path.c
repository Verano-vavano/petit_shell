/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:46:50 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/29 20:31:23 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"

static int	check_pathing(char *cmd)
{
	int		last_s;
	int		next_s;
	char	replaced_char;

	last_s = (cmd[0] == '/');
	next_s = ft_strchr_int(cmd + last_s, '/');
	while (cmd[last_s + next_s])
	{
		replaced_char = cmd[last_s + next_s];
		cmd[last_s + next_s] = '\0';
		if (access(cmd, X_OK) != 0)
		{
			cmd[last_s + next_s] = replaced_char;
			return (1);
		}
		cmd[last_s + next_s] = replaced_char;
		last_s += next_s + 1;
		next_s = ft_strchr_int(cmd + last_s, '/');
	}
	return (0);
}

char	*add_start(char *cmd)
{
	char	*n_cmd;

	n_cmd = ft_strjoin("./", cmd);
	if (!n_cmd)
		return (cmd);
	free(cmd);
	return (n_cmd);
}

int	check_org_path(char *cmd)
{
	int	pathing;

	if (cmd[ft_strchr_int(cmd, '/')] != '/')
		return (0);
	pathing = check_pathing(cmd);
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0 && !pathing)
			return (-1);
		else if (access(cmd, X_OK) != 0 || pathing)
			return (126);
		return (127);
	}
	return (0);
}

char	*check_path(char *path, char *path_cmd)
{
	char	*full_path;

	full_path = ft_strjoin(path, path_cmd);
	if (!full_path)
		return (0);
	if (access(full_path, X_OK) == 0)
	{
		free(path_cmd);
		return (full_path);
	}
	free(full_path);
	return (0);
}

bool	check_builtin(char *cmd, bool is_rel)
{
	if (is_rel)
		return (false);
	else if (!(ft_strcmp("hell", cmd)
			&& ft_strcmp("tetris", cmd)
			&& ft_strcmp("exit", cmd)
			&& ft_strcmp("echo", cmd)
			&& ft_strcmp("env", cmd)
			&& ft_strcmp("export", cmd) && ft_strcmp("unset", cmd)
			&& ft_strcmp("cd", cmd) && ft_strcmp("pwd", cmd)
			&& ft_strcmp("alias", cmd) && ft_strcmp("unalias", cmd)
			&& ft_strcmp(".", cmd) && ft_strcmp("source", cmd)
			&& ft_strcmp(":", cmd)))
		return (true);
	return (false);
}
