/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:08:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/18 17:54:49 by hdupire          ###   ########.fr       */
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

long	execute_the_line(t_command *cmd, t_env *env)
{
	int				n_cmd;
	long			err_status;
	char			**c_env;
	t_process_cmd	cmd_processing;
	t_ret_cmd		ret_cmd;

	n_cmd = count_cmds(cmd);
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
		printf("%ld\n", err_status);
		if (err_status && n_cmd == 1)
			return (err_status);
		err_status = get_cmd_path(&cmd_processing, env);
		printf("%ld %s\n", err_status, cmd_processing.cmd_name);
		if (err_status > 0 && n_cmd == 1)
		{
			free(cmd_processing.cmd);
			break ;
		}
		ret_cmd.n_cmd = n_cmd;
		create_child(&cmd_processing, c_env, &ret_cmd);
		waitpid(ret_cmd.pid, 0, 0);
		/*clean_processing(cmd_processing);*/
		cmd = go_to_next_cmd(cmd);
		if (cmd)
			printf("NOW = %s\n", cmd->content);
		n_cmd--;
		free(cmd_processing.cmd);
		free_redirs(cmd_processing.redir);
	}
	free_char_etoile_etoile(c_env);
	return (0);
}
