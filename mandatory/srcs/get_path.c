/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:08:42 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/11 20:22:11 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"

static int	rel_search(t_process_cmd *cmd, char *path)
{
	char	*path_cmd;
	char	*full_path;
	char	**paths;
	bool	path_ok;

	path_ok = (path && *path);
	paths = ft_split(path, ':');
	path_cmd = ft_strjoin("/", cmd->cmd_name);
	if (path_cmd == 0)
		return (1);
	while (*paths)
	{
		full_path = check_path(*paths, path_cmd);
		if (full_path)
		{
			cmd->free_name = true;
			cmd->cmd_name = full_path;
			return (0);
		}
		paths++;
	}
	free(path_cmd);
	if (!path_ok)
		return (128);
	return (127);
}

static int	check_rel(t_process_cmd *cmd)
{
	char	*now;
	int		last;

	last = 0;
	while (cmd->cmd_name[last])
	{
		last += ft_strchr_int(cmd->cmd_name + last, '/');
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
	cmd->free_name = true;
	relative = cmd->cmd_name[ft_strchr_int(cmd->cmd_name, '/')] == '/';
	if (relative && is_dir(cmd->cmd[0]))
		return (command_error(cmd->cmd[0], 125));
	cmd->is_builtin = check_builtin(cmd->cmd_name, relative);
	if (cmd->is_builtin)
		return (0);
	if (!env_isdefined("PATH", env))
		cmd->cmd_name = add_start(cmd->cmd_name);
	path = env_getval("PATH", env);
	err_catcher = check_org_path(cmd->cmd_name);
	if (err_catcher)
		return (command_error(cmd->cmd[0], err_catcher));
	else if (!env_isdefined("PATH", env) || relative)
		return (check_rel(cmd));
	err_catcher = rel_search(cmd, path);
	if (err_catcher != 0)
		return (command_error(cmd->cmd[0], err_catcher));
	return (0);
}
