/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:08:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/20 14:00:38 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

// dup2 STDIN && STDOUT from pipes
// dup2 everything else casually baby
static void	child_action(t_process_cmd *cmd, char **env, t_ret_cmd *ret)
{
	close(ret->pipes[0]);
	perform_redirections(cmd, ret);
	close(ret->pipes[1]);
	close(ret->fd);
	execve(cmd->cmd_name, cmd->cmd, env);
}

static void	create_child(t_process_cmd *cmd, char **env, t_ret_cmd *ret)
{
	ret->pid = fork();
	if (ret->pid == -1)
		perror("fork");
	else if (ret->pid == 0)
		child_action(cmd, env, ret);
	close(ret->pipes[1]);
	close(ret->fd);
	ret->fd = dup(ret->pipes[0]);
	close(ret->pipes[0]);
}

static t_command	*go_to_next_cmd(t_command *cmd)
{
	cmd = cmd->next;
	while (cmd && cmd->purpose != DELIM && cmd->purpose != CMD_DELIM)
		cmd = cmd->next;
	if (!cmd || cmd->purpose == CMD_DELIM)
		return (cmd);
	return (cmd->next);
}

static long	wait_father(pid_t pid, int n_cmd)
{
	int	exit_st;
	int	status;

	exit_st = -1;
	while (--n_cmd != -1)
	{
		if (waitpid(-1, &status, 0) == pid)
			exit_st = status;
	}
	if (exit_st == -1)
		exit_st = status;
	return (WEXITSTATUS(exit_st));
}

long	execute_the_line(t_command *cmd, t_env *env)
{
	int				n_cmd;
	int				n_cmd_cpy;
	long			err_status;
	char			**c_env;
	t_process_cmd	cmd_processing;
	t_ret_cmd		ret_cmd;

	n_cmd = count_cmds(cmd);
	n_cmd_cpy = n_cmd;
	c_env = re_char_etoile_etoilise_env(env);
	ret_cmd.pid = -1;
	ret_cmd.fd = -1;
	if (c_env == 0)
		return (1);
	while (n_cmd)
	{
		if (pipe(ret_cmd.pipes) < 0)
			continue ;
		cmd_processing.redir = 0;
		err_status = get_cmd(&cmd_processing, cmd);
		if (err_status && n_cmd == 1)
			return (err_status);
		err_status = get_cmd_path(&cmd_processing, env);
		if (err_status > 0 && n_cmd == 1)
		{
			free(cmd_processing.cmd);
			break ;
		}
		ret_cmd.n_cmd = n_cmd;
		create_child(&cmd_processing, c_env, &ret_cmd);
		/*clean_processing(cmd_processing);*/
		cmd = go_to_next_cmd(cmd);
		n_cmd--;
		free(cmd_processing.cmd);
		free_redirs(cmd_processing.redir);
		if (cmd_processing.free_name)
			free(cmd_processing.cmd_name);
	}
	wait_father(ret_cmd.pid, n_cmd_cpy);
	free_char_etoile_etoile(c_env);
	return (0);
}
