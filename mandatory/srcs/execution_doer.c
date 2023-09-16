/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_doer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:45:18 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/16 17:33:26 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

// dup2 STDIN && STDOUT from pipes
// dup2 everything else casually baby
static void	child(t_process_cmd *cmd, t_tool *t, char **c_env, t_ret_cmd *ret)
{
	close(ret->pipes[0]);
	perform_redirections(cmd, ret);
	close(ret->pipes[1]);
	close(ret->fd);
	if (ret->n_cmd == 1)
		print_ps0(t);
	if (cmd->is_builtin)
		exit(exec_bltin(cmd, t, false, c_env));
	else
		execve(cmd->cmd_name, cmd->cmd, c_env);
	exit(0);
}

void	crt_child(t_process_cmd *cmd, t_tool *t, t_ret_cmd *ret)
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

long	wait_father(t_ret_cmd *ret, int n_cmd, long err)
{
	int	exit_st;
	int	status;

	close(ret->fd);
	exit_st = -1;
	while (--n_cmd != -1)
	{
		if (waitpid(-1, &status, 0) == ret->pid)
			exit_st = status;
	}
	if (g_sig_rec)
		printfd(STDOUT_FILENO, "\n");
	if (exit_st == -1)
		exit_st = status;
	if (err)
		return (err);
	return (WEXITSTATUS(exit_st));
}

void	check_hist(t_command *cmd, t_hist *hist, t_env *env, int n_cmd)
{
	int	n;

	n = 0;
	if (hist && n_cmd == 1 && ft_strcmp(cmd->content, "exit") == 0)
	{
		while (cmd && cmd->purpose != CMD_DELIM && cmd->purpose != DELIM)
		{
			if (cmd->purpose == COMMAND)
				n++;
			if (n > 2)
				return ;
			cmd = cmd->next;
		}
		write_hist(hist, env);
		free_history(hist);
	}
}
