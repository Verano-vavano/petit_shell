/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:08:42 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/05 16:02:26 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	rel_search(t_process_cmd *cmd, char **path)
{
	char	*path_cmd;
	char	*full_path;

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
	return (-1);
}

// -1 = 0 = pas d'erreur
// > 0 = erreur
// . 1 = malloc
// . 126 = perm denied
// . 127 = not found
int	get_cmd_path(t_process_cmd *cmd, t_env *env)
{
	char	**path;
	int		err_catcher;
	bool	is_rel;

	cmd->cmd_name = ft_strdup(cmd->cmd[0]);
	cmd->free_name = true;
	is_rel = cmd->cmd_name[ft_strchr_int(cmd->cmd_name, '/')] == '/';
	cmd->is_builtin = check_builtin(cmd->cmd_name, is_rel);
	if (cmd->is_builtin)
		return (0);
	if (is_rel && access(cmd->cmd_name, F_OK) == 0)
		return (0);
	path = env_getval("PATH", env);
	if (!env_isdefined("PATH", env))
		cmd->cmd_name = add_start(cmd->cmd_name);
	err_catcher = check_org_path(cmd->cmd_name);
	if (err_catcher)
		return (command_error(cmd->cmd[0], err_catcher));
	else if (!env_isdefined("PATH", env) || is_rel)
		return (command_error(cmd->cmd[0], 127));
	err_catcher = rel_search(cmd, path);
	if (err_catcher != -1)
		return (err_catcher);
	return (command_error(cmd->cmd[0], 127));
}
