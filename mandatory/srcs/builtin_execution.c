/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 23:17:30 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/10 23:06:47 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static long	more_bltn(t_process_cmd *cmd, t_tool *t, bool one)
{
	int	pid;

	if (ft_strcmp("exit", cmd->cmd_name) == 0 && !cmd->sub_cmd)
	{
		if (one)
			printfd(STDOUT_FILENO, "exit\n");
		return (exit_hell(cmd->cmd, t->rt_val, t, one));
	}
	else if (ft_strcmp("tetris", cmd->cmd_name) == 0 && one)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		else if (pid == 0)
			exit(tetris(cmd->cmd));
		else
			return (0 * waitpid(pid, 0, 0));
	}
	else if (ft_strcmp(".", cmd->cmd_name) == 0
		|| ft_strcmp("source", cmd->cmd_name) == 0)
		return (source_of_styx(cmd->cmd, t));
	else if (ft_strcmp("history", cmd->cmd_name) == 0)
		return (beastory(cmd->cmd, t));
	else if (ft_strcmp("[", cmd->cmd_name) == 0 || ft_strcmp(cmd->cmd_name, "test") == 0)
		return (test_satanism(cmd->cmd, true));
	return (0);
}

static long	find_exec_bltn(t_process_cmd *cmd, t_tool *t, bool one)
{
	if (ft_strcmp("hell", cmd->cmd_name) == 0)
		return (metal_injection());
	else if (ft_strcmp("echo", cmd->cmd_name) == 0)
		return (echo_des_enfers(cmd->cmd));
	else if (ft_strcmp("printf", cmd->cmd_name) == 0)
		return (printferno(cmd->cmd));
	else if (ft_strcmp("pff", cmd->cmd_name) == 0)
		return (print_formated_hell(cmd->cmd));
	else if (ft_strcmp("env", cmd->cmd_name) == 0)
		return (env_infernal(t->env, false));
	else if (ft_strcmp("export", cmd->cmd_name) == 0 && !cmd->sub_cmd)
		return (les_ex_portes_de_lenfer(cmd->cmd, &(t->env)));
	else if (ft_strcmp("unset", cmd->cmd_name) == 0 && !cmd->sub_cmd)
		return (unset_et_damnation(cmd->cmd, &(t->env)));
	else if (ft_strcmp("cd", cmd->cmd_name) == 0 && !cmd->sub_cmd)
		return (cd_mentiel(cmd->cmd, &t));
	else if (ft_strcmp("pwd", cmd->cmd_name) == 0)
		return (print_working_damnation(t->cwd));
	else if (ft_strcmp("alias", cmd->cmd_name) == 0 && !cmd->sub_cmd)
		return (hellias(cmd->cmd, t));
	else if (ft_strcmp("unalias", cmd->cmd_name) == 0 && !cmd->sub_cmd)
		return (unhellias(cmd->cmd, t));
	else
		return (more_bltn(cmd, t, one));
}

static void	builtin_redirections(t_redir_pipe *redir)
{
	while (redir)
	{
		if (redir->fd_end == STDIN_FILENO && redir->fd_read != -1)
			dup2(redir->fd_read, STDIN_FILENO);
		if (redir->fd_end == STDOUT_FILENO && redir->fd_write != -1)
			dup2(redir->fd_write, STDOUT_FILENO);
		if (redir->fd_end == STDERR_FILENO && redir->fd_write != -1)
			dup2(redir->fd_write, STDERR_FILENO);
		redir = redir->next;
	}
}

static void	redir_back(int in, int out, int err)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	dup2(err, STDERR_FILENO);
	close(in);
	close(out);
	close(err);
}

long	exec_bltin(t_process_cmd *cmd, t_tool *t, bool one)
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
		print_ps0(t);
	}
	ret_val = find_exec_bltn(cmd, t, one);
	if (one)
		redir_back(save_in, save_out, save_err);
	close_files(cmd->redir);
	exec_cleaner(*cmd);
	return (ret_val);
}
