/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:08:42 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/15 20:48:39 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	check_pathing(char *cmd)
{
	int		last_s;
	int		next_s;
	char	replaced_char;

	last_s = 0;
	next_s = ft_strchr_int(cmd + last_s, '/');
	while (cmd[last_s + next_s])
	{
		replaced_char = cmd[last_s + next_s];
		cmd[last_s + next_s] = 0;
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

static char	*add_start(char *cmd)
{
	char	*n_cmd;

	n_cmd = ft_strjoin("./", cmd);
	if (!n_cmd)
		return (cmd);
	free(cmd);
	return (n_cmd);
}

static int	check_org_path(char *cmd)
{
	int	pathing;

	if (cmd[ft_strchr_int(cmd, '/')] != '/')
		return (0);
	pathing = check_pathing(cmd);
	if (access(cmd, F_OK) == 0 || pathing)
	{
		if (access(cmd, X_OK) == 0)
			return (-1);
		perror(cmd);
		return (126);
	}
	return (0);
}

static char	*check_path(char **paths, char *path_cmd)
{
	char	*full_path;

	full_path = ft_strjoin(*paths, path_cmd);
	if (full_path == 0)
		return (0);
	if (access(full_path, X_OK) == 0)
	{
		free(path_cmd);
		return (full_path);
	}
	free(full_path);
	return (0);
}

// -1 = 0 = pas d'erreur
// > 0 = erreur
// .-1 = malloc
// .-126 = perm denied
// .-127 = not found
int	get_cmd_path(t_process_cmd *cmd, t_env *env)
{
	char	**path;
	char	*path_cmd;
	char	*full_path;
	int		err_catcher;

	cmd->cmd_name = cmd->cmd[0];
	path = env_getval("PATH", env);
	if (!env_isdefined("PATH", env))
		cmd->cmd_name = add_start(cmd->cmd_name);
	err_catcher = check_org_path(cmd->cmd_name);
	if (err_catcher)
		return (err_catcher);
	else if (!env_isdefined("PATH", env))
	{
		perror(cmd->cmd[0]);
		return (127);
	}
	path_cmd = ft_strjoin("/", cmd->cmd_name);
	if (path_cmd == 0)
		return (1);
	while (*path)
	{
		full_path = check_path(path, path_cmd);
		if (full_path)
		{
			cmd->cmd_name = full_path;
			return (1);
		}
		path++;
	}
	free(path_cmd);
	if (cmd->cmd_name[ft_strchr_int(cmd->cmd_name, '/')])
		perror(cmd->cmd_name);
	return (127);
}
