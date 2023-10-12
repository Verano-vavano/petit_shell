/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_doer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:45:18 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/12 17:45:31 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

// dup2 STDIN && STDOUT from pipes
// dup2 everything else casually baby
static void	child(t_process_cmd *cmd, t_tool *t, char **c_env, t_ret_cmd *ret)
{
	t_tool	empty_tool;

	close(ret->pipes[0]);
	perform_redirections(cmd, ret);
	close(ret->pipes[1]);
	close(ret->fd);
	if (ret->n_cmd == 1)
		print_ps0(t);
	if (cmd->is_parenthesis)
	{
		empty_tool.env = t->env;
		empty_tool.alias_start = t->alias_start;
		empty_tool.alias_end = t->alias_end;
		empty_tool.hist = 0;
		exit(cmd_processing(ft_strndup(cmd->cmd[0] + 1,
					ft_strlen(cmd->cmd[0]) - 2), &empty_tool, false));
	}
	if (cmd->is_builtin)
		exit(exec_bltin(cmd, t, false));
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

	if (ret->fd != -1)
		close(ret->fd);
	exit_st = -1;
	status = 0;
	while (--n_cmd != -1)
	{
		if (waitpid(-1, &status, 0) == ret->pid)
			exit_st = status;
	}
	if (g_sig_rec == SIGINT)
		printfd(STDOUT_FILENO, "\n");
	else if (g_sig_rec == SIGQUIT)
		printf("Quit (core dumped)\n");
	if (exit_st == -1)
		exit_st = status;
	if (err)
		return (err);
	return (WEXITSTATUS(exit_st));
}

void	check_hist(t_command *cmd, t_tool *tool, int n_cmd)
{
	t_hist	*hist;
	int		n;

	n = 0;
	hist = tool->hist;
	if (hist && n_cmd == 1 && cmd->content
		&& ft_strcmp(cmd->content, "exit") == 0)
	{
		while (cmd && cmd->purpose != CMD_DELIM && cmd->purpose != DELIM)
		{
			if (cmd->purpose == COMMAND)
				n++;
			if (n > 2)
				return ;
			cmd = cmd->next;
		}
		if (tool && tool->settings.hist)
			write_hist(hist, tool->env);
		free_history(hist, true);
	}
}
