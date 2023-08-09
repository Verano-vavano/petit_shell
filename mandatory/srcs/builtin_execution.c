/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 23:17:30 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/26 14:59:04 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

long	find_and_execute_builtin(t_process_cmd *cmd, t_env *env)
{
	if (ft_strcmp("hell", cmd->cmd_name) == 0)
		return (metal_injection());
	else if (ft_strcmp("exit", cmd->cmd_name) == 0)
		exit_hell(cmd->cmd);
	else if (ft_strcmp("echo", cmd->cmd_name) == 0)
		return (echo_des_enfers(cmd->cmd));
	else if (ft_strcmp("env", cmd->cmd_name) == 0)
		return (env_infernal(env, NULL));
	else if (ft_strcmp("export", cmd->cmd_name) == 0)
		return (les_ex_portes_de_lenfer(cmd->cmd, env)); // crash env-i && add pas + leaks
	else if (ft_strcmp("unset", cmd->cmd_name) == 0)
		return (unset_et_damnation(cmd->cmd, env));
	else if (ft_strcmp("cd", cmd->cmd_name) == 0)
		return (cd_mentiel(cmd->cmd, env));
	else if (ft_strcmp("pwd", cmd->cmd_name) == 0)
		return (print_working_damnation());
	return (1);
}

static void	builtin_redirections(t_redir_pipe *redir)
{
	while (redir)
	{
		if (redir->fd_end == STDIN_FILENO && redir->fd_read != -1)
			dup2(redir->fd_read, STDIN_FILENO);
		else if (redir->fd_end == STDOUT_FILENO && redir->fd_write != -1)
			dup2(redir->fd_write, STDOUT_FILENO);
		else if (redir->fd_end == STDERR_FILENO && redir->fd_write != -1)
			dup2(redir->fd_write, STDERR_FILENO);
		redir = redir->next;
	}
}

long	execute_builtin(t_process_cmd *cmd, t_env *env, bool one)
{
	long	ret_val;
	int		save_in;
	int		save_out;
	int		save_err;

	if (one)
	{
		save_in = dup(STDIN_FILENO);
		save_out = dup(STDOUT_FILENO);
		save_err = dup(STDERR_FILENO);
		builtin_redirections(cmd->redir);
	}
	ret_val = find_and_execute_builtin(cmd, env);
	if (one)
	{
		dup2(save_in, STDIN_FILENO);
		dup2(save_out, STDOUT_FILENO);
		dup2(save_err, STDERR_FILENO);
	}
	exec_cleaner(*cmd);
	return (ret_val);
}
