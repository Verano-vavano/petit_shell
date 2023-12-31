/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:08:42 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/10 13:39:15 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"

static bool	path_check(char **paths, char *path_cmd, t_process_cmd *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = check_path(paths[i], path_cmd);
		if (full_path)
		{
			if (cmd->cmd_name)
				free(cmd->cmd_name);
			cmd->cmd_name = full_path;
			free_char_etoile_etoile(paths);
			return (true);
		}
		i++;
	}
	return (false);
}

static int	rel_search(t_process_cmd *cmd, char *path)
{
	char	**paths;
	char	*path_cmd;

	if (!path)
		paths = ft_split("./", ':');
	else
		paths = ft_split(path, ':');
	if (!paths)
		return (1);
	path_cmd = ft_strjoin("/", cmd->cmd_name);
	if (!path_cmd)
	{
		free_char_etoile_etoile(paths);
		return (1);
	}
	if (path_check(paths, path_cmd, cmd))
		return (0);
	free_char_etoile_etoile(paths);
	free(path_cmd);
	return (127 * (path != 0) + 128 * (path == 0));
}

static int	check_rel(t_process_cmd *cmd)
{
	char	*now;
	int		last;

	last = 0;
	while (cmd && cmd->cmd_name && cmd->cmd_name[last])
	{
		last += ft_strchr_int(cmd->cmd_name + last, '/');
		if (!cmd->cmd_name[last])
			return (0);
		now = ft_strndup(cmd->cmd_name, last + 1);
		if (!is_dir(now) && access(now, F_OK) != 0)
		{
			free(now);
			return (command_error(cmd->cmd[0], 128));
		}
		if (access(now, X_OK) != 0)
		{
			free(now);
			return (command_error(cmd->cmd[0], 126));
		}
		free(now);
		last++;
	}
	return (0);
}

// -1 = 0 = pas d'erreur
// > 0 = erreur
// . 1 = malloc
// . 126 = perm denied
// . 127 = not found
int	get_cmd_path(t_process_cmd *cmd, t_env *env)
{
	char	*path;
	int		err_catcher;
	bool	relative;

	cmd->cmd_name = ft_strdup(cmd->cmd[0]);
	if (!cmd->cmd_name)
		return (1);
	relative = cmd->cmd_name[ft_strchr_int(cmd->cmd_name, '/')] == '/';
	if (relative && is_dir(cmd->cmd[0]))
		return (command_error(cmd->cmd[0], 125));
	cmd->is_builtin = check_builtin(cmd->cmd_name, relative);
	if (cmd->is_builtin)
		return (0);
	path = env_getval("PATH", env);
	err_catcher = check_org_path(cmd->cmd_name);
	if (err_catcher)
		return (command_error(cmd->cmd[0], err_catcher));
	else if (!path || !(*path) || relative)
		err_catcher = check_rel(cmd);
	if (err_catcher)
		return (err_catcher);
	err_catcher = rel_search(cmd, path);
	if (err_catcher != 0)
		return (command_error(cmd->cmd[0], err_catcher));
	return (0);
}
