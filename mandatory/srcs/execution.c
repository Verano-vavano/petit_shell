/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:08:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/05 15:56:51 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	close_pipes(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
}

static long	c_get(t_process_cmd *c_p, t_command **cmd, t_ret_cmd *r, int *n)
{
	long	err_status;

	c_p->redir = 0;
	err_status = get_cmd(c_p, *cmd, r->heredoc_no);
	if (err_status && n[0] == 1)
		return (-1);
	else if (!c_p->cmd || !(*(c_p->cmd)))
	{
		close_pipes(r->pipes);
		n[0]--;
		n[1]--;
		if (r->fd != -1)
			close(r->fd);
		r->fd = -2;
		*cmd = go_to_next_cmd(*cmd);
		return (1);
	}
	return (0);
}

static long	aexec(t_process_cmd *c_p, t_tools *t, t_ret_cmd *ret, int *n_cmd)
{
	ret->n_cmd = n_cmd[0];
	if (c_p->is_builtin && n_cmd[1] == 1)
	{
		close_pipes(ret->pipes);
		return (exec_bltin(c_p, t, true, t->c_env));
	}
	else
		crt_child(c_p, t, ret);
	n_cmd[0]--;
	exec_cleaner(*c_p);
	return (-1);
}

static long	ex_loop(t_command *cmd, t_tools *tools, t_ret_cmd *ret, int *n_cmd)
{
	long			err_status;
	t_process_cmd	cmd_processing;

	while (n_cmd[0])
	{
		if (pipe(ret->pipes) < 0)
			continue ;
		cmd_processing.sub_cmd = !(tools->hist);
		err_status = c_get(&cmd_processing, &cmd, ret, n_cmd);
		if (err_status == -1)
			break ;
		else if (err_status == 1)
			continue ;
		err_status = get_cmd_path(&cmd_processing, tools->env);
		if (err_status > 0 && n_cmd[0] == 1)
		{
			free(cmd_processing.cmd);
			break ;
		}
		err_status = aexec(&cmd_processing, tools, ret, n_cmd);
		if (err_status != -1)
			return (err_status);
		cmd = go_to_next_cmd(cmd);
	}
	return (wait_father(ret, n_cmd[1] - n_cmd[0], err_status));
}

long	execute_the_line(t_command *cmd, t_tools *tools, int *heredoc_no)
{
	int				n_cmd[2];
	int				ret;
	t_ret_cmd		ret_cmd;

	ret_cmd.heredoc_no = heredoc_no;
	while (cmd && cmd->purpose != CMD_DELIM && cmd->purpose != COMMAND)
		cmd = cmd->next;
	n_cmd[0] = count_cmds(cmd);
	n_cmd[1] = n_cmd[0];
	if (!cmd || cmd->purpose == CMD_DELIM)
		return (0);
	tools->c_env = re_char_etoile_etoilise_env(tools->env);
	ret_cmd.pid = -1;
	ret_cmd.fd = -1;
	check_hist(cmd, tools->hist, tools->env, n_cmd[0]);
	ret = ex_loop(cmd, tools, &ret_cmd, n_cmd);
	if (tools->c_env)
		free_char_etoile_etoile(tools->c_env);
	return (ret);
}
