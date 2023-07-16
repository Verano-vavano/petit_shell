/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:08:52 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/16 15:51:32 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

// dup2 STDIN && STDOUT from pipes
// dup2 everything else casually baby
static void	child_action(t_process_cmd *cmd, char **env)
{
	perform_redirections(cmd);
	execve(cmd->cmd_name, cmd->cmd, env);
}

static pid_t	create_child(t_process_cmd *cmd, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
		child_action(cmd, env);
	return (pid);
}

long	execute_the_line(t_command *cmd, t_env *env)
{
	pid_t			last_pid;
	int				n_cmd;
	long			err_status;
	char			**c_env;
	t_process_cmd	cmd_processing;

	n_cmd = count_cmds(cmd);
	c_env = re_char_etoile_etoilise_env(env);
	if (c_env == 0)
		return (1);
	while (n_cmd)
	{
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
			return (err_status);
		}
		last_pid = create_child(&cmd_processing, env);
		waitpid(-1, 0, 0);
		/*clean_processing(cmd_processing);
		cmd = go_to_next_cmd(cmd);*/
		n_cmd--;
		free(cmd_processing.cmd);
		if (cmd_processing.free_name)
			free(cmd_processing.cmd_name);
		free_redirs(cmd_processing.redir);
	}
	free(c_env);
	return (0);
}
