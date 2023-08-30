/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:08:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/30 16:35:16 by hdupire          ###   ########.fr       */
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

void	crt_child(t_process_cmd *cmd, t_tools *t, char **c_env, t_ret_cmd *ret)
{
	ret->pid = fork();
	if (ret->pid == -1)
		perror("fork");
	else if (ret->pid == 0)
		child(cmd, t, c_env, ret);
	close(ret->pipes[1]);
	close(ret->fd);
	ret->fd = dup(ret->pipes[0]);
	close(ret->pipes[0]);
	close_files(cmd->redir);
}

static long	wait_father(pid_t pid, int n_cmd, char **c_env, long err)
{
	int	exit_st;
	int	status;

	if (c_env)
		free_char_etoile_etoile(c_env);
	exit_st = -1;
	while (--n_cmd != -1)
	{
		if (waitpid(-1, &status, 0) == pid)
			exit_st = status;
	}
	if (exit_st == -1)
		exit_st = status;
	if (!err)
		return (WEXITSTATUS(exit_st));
	return (err);
}

static void	check_hist(t_command *cmd, t_hist *hist, t_env *env, int n_cmd)
{
	if (hist && n_cmd == 1 && ft_strcmp(cmd->content, "exit") == 0)
	{
		write_hist(hist, env);
		free_history(hist);
	}
}

long	execute_the_line(t_command *cmd, t_tools *tools, int *heredoc_no)
{
	int				n_cmd[2];
	long			err_status;
	char			**c_env;
	t_process_cmd	cmd_processing;
	t_ret_cmd		ret_cmd;

	while (cmd && cmd->purpose != CMD_DELIM && cmd->purpose != COMMAND)
		cmd = cmd->next;
	n_cmd[0] = count_cmds(cmd);
	n_cmd[1] = n_cmd[0];
	c_env = re_char_etoile_etoilise_env(tools->env);
	if (!cmd || cmd->purpose == CMD_DELIM)
		return (0);
	ret_cmd.pid = -1;
	ret_cmd.fd = -1;
	check_hist(cmd, tools->hist, tools->env, n_cmd[0]);
	while (n_cmd[0])
	{
		if (pipe(ret_cmd.pipes) < 0)
			continue ;
		cmd_processing.redir = 0;
		cmd_processing.sub_cmd = !(tools->env);
		err_status = get_cmd(&cmd_processing, cmd, heredoc_no);
		if (err_status && n_cmd[0] == 1)
			break ;
		else if (!cmd_processing.cmd || !(*(cmd_processing.cmd)))
		{
			close(ret_cmd.pipes[0]);
			close(ret_cmd.pipes[1]);
			n_cmd[0]--;
			n_cmd[1]--;
			if (ret_cmd.fd != -1)
				close(ret_cmd.fd);
			ret_cmd.fd = -2;
			cmd = go_to_next_cmd(cmd);
			continue ;
		}
		err_status = get_cmd_path(&cmd_processing, tools->env);
		if (err_status > 0 && n_cmd[0] == 1)
		{
			free(cmd_processing.cmd);
			break ;
		}
		ret_cmd.n_cmd = n_cmd[0];
		if (cmd_processing.is_builtin && n_cmd[1] == 1)
		{
			close(ret_cmd.pipes[0]);
			close(ret_cmd.pipes[1]);
			return (exec_bltin(&cmd_processing, tools, true, c_env));
		}
		else
			crt_child(&cmd_processing, tools, c_env, &ret_cmd);
		cmd = go_to_next_cmd(cmd);
		n_cmd[0]--;
		exec_cleaner(cmd_processing);
	}
	close(ret_cmd.fd);
	return (wait_father(ret_cmd.pid, n_cmd[1] - n_cmd[0], c_env, err_status));
}
