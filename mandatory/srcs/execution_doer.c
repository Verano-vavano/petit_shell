/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_doer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:45:18 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/01 14:58:54 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

// dup2 STDIN && STDOUT from pipes
// dup2 everything else casually baby
static void	child(t_process_cmd *cmd, t_tools *t, char **c_env, t_ret_cmd *ret)
{
	close(ret->pipes[0]);
	perform_redirections(cmd, ret);
	close(ret->pipes[1]);
	close(ret->fd);
	if (cmd->is_builtin)
		exit(exec_bltin(cmd, t, false, c_env));
	else
		execve(cmd->cmd_name, cmd->cmd, c_env);
	exit(0);
}

void	crt_child(t_process_cmd *cmd, t_tools *t, t_ret_cmd *ret)
{
	ret->pid = fork();
	if (ret->pid == -1)
		perror("fork");
	else if (ret->pid == 0)
		child(cmd, t, t->c_env, ret);
	close(ret->pipes[1]);
	close(ret->fd);
	ret->fd = dup(ret->pipes[0]);
	close(ret->pipes[0]);
	close_files(cmd->redir);
}

long	wait_father(t_ret_cmd *ret, int n_cmd, char **c_env, long err)
{
	int	exit_st;
	int	status;

	close(ret->fd);
	if (c_env)
		free_char_etoile_etoile(c_env);
	exit_st = -1;
	while (--n_cmd != -1)
	{
		if (waitpid(-1, &status, 0) == ret->pid)
			exit_st = status;
	}
	if (exit_st == -1)
		exit_st = status;
	if (!err)
		return (WEXITSTATUS(exit_st));
	return (err);
}

void	check_hist(t_command *cmd, t_hist *hist, t_env *env, int n_cmd)
{
	if (hist && n_cmd == 1 && ft_strcmp(cmd->content, "exit") == 0)
	{
		write_hist(hist, env);
		free_history(hist);
	}
}
