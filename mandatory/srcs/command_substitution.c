/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:37:31 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/24 19:04:22 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	find_end_comm(char *s)
{
	int		i;
	int		inside;
	char	quoted;

	i = 1;
	inside = 0;
	quoted = 0;
	while (s[i])
	{
		quoted = is_quoted(s, i, quoted);
		if (s[i] == '(' && !quoted)
			inside++;
		else if (s[i] == ')' && !quoted && !inside)
			return (i);
		else if (s[i] == ')' && !quoted)
			inside--;
		i++;
	}
	return (i);
}

static char	*get_output(int *pipes)
{
	char	buffer[1024];
	char	*ret;
	char	*temp;
	int		readed;

	ret = ft_calloc(1, sizeof (char));
	if (!ret)
		return (0);
	readed = 1023;
	close(pipes[1]);
	while (readed == 1023)
	{
		readed = read(pipes[0], buffer, 1023);
		if (readed == 0 || readed == -1)
			break ;
		buffer[readed] = 0;
		temp = ft_strjoin(ret, buffer);
		free(ret);
		if (!temp)
			return (0);
		ret = temp;
	}
	ret[ft_strlen(ret) - 1] = 0;
	return (ret);
}

static long	perform_exec(t_command *cmd, t_env *env, int start, bool repl)
{
	long	se[3];
	int		stdout_fd;
	int		pipes[2];
	char	*cmd_sent;
	char	*out;

	se[0] = start - repl;
	se[1] = find_end_comm(cmd->content + start) + repl;
	if (repl)
	{
		if (pipe(pipes) == -1)
			return (1);
		stdout_fd = dup(STDOUT_FILENO);
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
		{
			dup2(STDOUT_FILENO, stdout_fd);
			return (1);
		}
	}
	cmd_sent = ft_strndup(cmd->content + se[0] + repl + 1, se[1] - 1 - repl);
	se[3] = 1;
	if (cmd_sent)
		se[3] = cmd_processing(cmd_sent, env, false);
	printf("\n");
	if (repl)
	{
		dup2(stdout_fd, STDOUT_FILENO);
		out = get_output(pipes);
		if (out && *out)
			cmd->content = ft_strreplace(cmd->content, se[0], se[1] + 1, out);
		else
			cmd->content = ft_strreplace(cmd->content, se[0], se[1] + 1, "\0");
		if (out)
			free(out);
	}
	return (se[3]);
}

static long	srch_exec_comm(t_command *cmd, t_env *env)
{
	bool	repl;
	char	quoted;
	int		start;
	long	ret;

	quoted = 0;
	start = 0;
	while (cmd->content[start])
	{
		quoted = is_quoted(cmd->content, start, quoted);
		if (cmd->content[start] == '(' && !quoted)
		{
			if (start != 0 && cmd->content[start - 1] == '$')
				repl = true;
			ret = perform_exec(cmd, env, start, repl);
		}
		start++;
	}
	if (!repl)
		return (ret);
	else
		return (-1);
}

long	command_substitution(t_command *cmd, t_env *env)
{
	bool	skip_first;
	long	ret;

	skip_first = false;
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		if (ft_strchr(cmd->content, '(') && ft_strchr(cmd->content, ')'))
		{
			ret = srch_exec_comm(cmd, env);
			if (ret >= 0 && !skip_first)
				skip_first = true;
		}
		cmd = cmd->next;
	}
	if (skip_first)
		return (ret);
	else
		return (-1);
}
