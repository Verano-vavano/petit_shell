/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_mainloop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:03:32 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/18 11:01:15 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static long	c_get(t_process_cmd *c_p, t_command **cmd, t_ret_cmd *r, int *n)
{
	long	err_status;

	c_p->redir = NULL;
	err_status = get_cmd(c_p, *cmd, r->heredoc_no);
	if (err_status && n[0] != 1)
	{
		r->fd = dup(r->pipes[0]);
		return (err_status);
	}
	else if (err_status && n[0] == 1)
		return (err_status * (-1));
	else if (!c_p->cmd || !(*(c_p->cmd)))
	{
		r->fd = dup(r->pipes[0]);
		close_pipes(r->pipes);
		n[0]--;
		n[1]--;
		if (r->fd != -1)
			close(r->fd);
		r->fd = -2;
		return (1);
	}
	return (0);
}

static long	aexec(t_process_cmd *c_p, t_tool *t, t_ret_cmd *ret, int *n_cmd)
{
	ret->n_cmd = n_cmd[0];
	n_cmd[0]--;
	if (c_p->is_builtin && n_cmd[1] == 1)
	{
		close_pipes(ret->pipes);
		return (exec_bltin(c_p, t, true, t->c_env));
	}
	else
		crt_child(c_p, t, ret);
	exec_cleaner(*c_p);
	return (-1);
}

static long	c_get_ret(long err_status, t_ret_cmd *ret, int *n_cmd)
{
	if (err_status < 0)
		return (err_status * (-1));
	else if (err_status > 0)
	{
		ret->fd = dup(ret->pipes[0]);
		close_pipes(ret->pipes);
		n_cmd[0]--;
		return (err_status * (-1));
	}
	return (0);
}

static void	init_cp(t_process_cmd *cmd_processing, t_tool *tool, t_command *cmd)
{
	cmd_processing->is_builtin = false;
	cmd_processing->is_parenthesis = (cmd && cmd->content
			&& cmd->content[0] == '(' && ft_strchr(cmd->content, ')'));
	cmd_processing->cmd_name = 0;
	cmd_processing->sub_cmd = !(tool->hist);
}

// RET > 0 : break
// RET < 0 : continue
// RET == 0 : no error
long	ex_loop(t_command **cmd, t_tool *tool, t_ret_cmd *ret, int *n_cmd)
{
	long			err_status;
	t_process_cmd	cmd_processing;

	if (pipe(ret->pipes) < 0)
		return (1);
	init_cp(&cmd_processing, tool, *cmd);
	err_status = c_get(&cmd_processing, cmd, ret, n_cmd);
	if (cmd && *cmd)
		*cmd = go_to_next_cmd(*cmd);
	if (err_status)
		return (c_get_ret(err_status, ret, n_cmd));
	else if (!cmd_processing.cmd || !cmd_processing.cmd[0])
		return (1);
	if (!cmd_processing.is_parenthesis)
		err_status = get_cmd_path(&cmd_processing, tool->env);
	if (err_status > 0 && n_cmd[0] == 1)
	{
		free(cmd_processing.cmd_name);
		free(cmd_processing.cmd);
		return (err_status);
	}
	err_status = aexec(&cmd_processing, tool, ret, n_cmd);
	if (err_status != -1)
		return (err_status);
	return (0);
}
