/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:08:42 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/21 09:06:58 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static bool	check_builtin(char *cmd, bool is_rel)
{
	if (is_rel)
		return (false);
	else if (!(ft_strcmp("hell", cmd)
		&& ft_strcmp("exit", cmd)
		&& ft_strcmp("echo", cmd)
		&& ft_strcmp("env", cmd)
		&& ft_strcmp("export", cmd)
		&& ft_strcmp("unset", cmd)
		&& ft_strcmp("cd", cmd)
		&& ft_strcmp("pwd", cmd)))
		return (true);
	return (false);
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
	bool	is_rel;

	cmd->cmd_name = cmd->cmd[0];
	cmd->free_name = false;
	is_rel = cmd->cmd_name[ft_strchr_int(cmd->cmd_name, '/')] == '/';
	cmd->is_builtin = check_builtin(cmd->cmd_name, is_rel);
	if (cmd->is_builtin)
		return (0);
	path = env_getval("PATH", env);
	if (!env_isdefined("PATH", env))
		cmd->cmd_name = add_start(cmd->cmd_name);
	err_catcher = check_org_path(cmd->cmd_name);
	if (err_catcher)
		return (command_error(cmd->cmd[0], err_catcher));
	else if (!env_isdefined("PATH", env) || is_rel)
		return (command_error(cmd->cmd[0], 127));
	path_cmd = ft_strjoin("/", cmd->cmd_name);
	if (path_cmd == 0)
		return (1);
	while (*path)
	{
		full_path = check_path(path, path_cmd);
		if (full_path)
		{
			cmd->free_name = true;
			cmd->cmd_name = full_path;
			return (0);
		}
		path++;
	}
	free(path_cmd);
	return (command_error(cmd->cmd[0], 127));
}
