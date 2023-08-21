/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 07:48:54 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/21 11:27:32 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

/*
 * SE[0] = start of the *
 * SE[1] = end of the *
 * SE[2] = start of next *, -1 if no occurence
 */

static bool	is_valid_fe(char *file, int *se, char **se_strs)
{
	char	*ending;

	if ((!se_strs[0] || se_strs[0][0] != '.') && file[0] == '.')
		return (false);
	if (se_strs[0] && ft_strstr(file, se_strs[0]) != file)
		return (false);
	if (se_strs[1] && se[2] == -1)
	{
		ending = ft_strstr(file + se[1], se_strs[1]);
		printf("%s : %s\n", file, ending);
		if (!ending || ending[ft_strlen(se_strs[1]) - 1] != 0)
		return (false);
	}
	else if (se_strs[1] && se[2] != -1)
	{
		se_strs[1][se[2] - 1] = 0;
		if (ft_strstr(file + se[1], se_strs[1]) == 0)
		{
			se_strs[1][se[2] - 1] = '*';
			return (false);
		}
		se_strs[1][se[2] - 1] = '*';
	}
	return (true);
}

static int	is_more_expand(char *s)
{
	int		i;
	char	quoted;

	i = 0;
	while (s[i] == '*')
		i++;
	quoted = 0;
	while (s[i])
	{
		quoted = is_quoted(s, i, quoted);
		if (!quoted && (s[i] == '*'))
			return (i);
		i++;
	}
	return (-1);
}

static void	perform_file_exp(t_command *cmd, int *se, char **se_strs, char *path)
{
	DIR				*dir;
	struct dirent	*file;

	se[2] = is_more_expand(cmd->content + se[0]);
	if (path)
		dir = opendir(path);
	else
		dir = opendir("./");
	file = readdir(dir);
	while (file)
	{
		// if valid, add to linked list
		if (is_valid_fe(file->d_name, se, se_strs))
			printf("%s%s\n", path, file->d_name);
		file = readdir(dir);
	}
	closedir(dir);
	// sort linked list
	// add to t_command
	(void) cmd;
	(void) se_strs;
}

static char	*get_end_fe(char *cnt, int end)
{
	int		i;
	char	quoted;

	if (!cnt[end] || cnt[end] == '/')
		return (0);
	i = 0;
	quoted = 0;
	while (cnt[end + i])
	{
		quoted = is_quoted(cnt, end + i, quoted);
		if (!quoted && cnt[end + i] == '/')
			break ;
		i++;
	}
	return (ft_strndup(cnt + end, i));
}

static char	*get_path_fe(char *cnt, int start)
{
	char	*path;
	char	quoted;
	int		last_s;
	int		i;

	quoted = 0;
	last_s = 0;
	i = 0;
	path = 0;
	while (cnt[i] && i < start)
	{
		quoted = is_quoted(cnt, i, quoted);
		if (!quoted && cnt[i] == '/')
			last_s = i;
		i++;
	}
	if (last_s != 0 || cnt[0] == '/')
		path = ft_strndup(cnt, last_s + 1);
	return (path);
}

static int	init_file_exp(t_command *cmd, int *se)
{
	char	*path;
	char	**se_strs;
	int		len_path;

	path = get_path_fe(cmd->content, se[0]);
	len_path = 0;
	if (path)
		len_path = ft_strlen(path);
	if (path && !is_dir(path))
		return (1);
	se_strs = ft_calloc(2, sizeof (char *));
	if (!se_strs)
		return (1);
	if (se[0] - len_path != 0)
		se_strs[0] = ft_strndup(cmd->content + len_path, se[0] - len_path);
	se_strs[1] = get_end_fe(cmd->content, se[0] + se[1]);
	perform_file_exp(cmd, se, se_strs, path);
	free(path);
	if (se_strs[0])
		free(se_strs[0]);
	if (se_strs[1])
		free(se_strs[1]);
	free(se_strs);
	return (0);
}

static void	filename_expand_it(t_command *cmd)
{
	int		se[3];
	char	quoted;
	bool	expanded;
	int		err;

	se[0] = 0;
	se[1] = 1;
	quoted = 0;
	expanded = false;
	while (cmd->content[se[0]])
	{
		quoted = is_quoted(cmd->content, se[0], quoted);
		if (cmd->content[se[0]] == '*' && !quoted)
		{
			while (cmd->content[se[0] + se[1]] == '*')
				se[1]++;
			err = init_file_exp(cmd, se);
			expanded = true;
			break ;
		}
		se[0]++;
	}
	(void) expanded;
	(void) err;
	/*if (expanded && !err)
		filename_expand_it(cmd);*/
}

void	filename_expansion(t_command *cmd)
{
	signal(SIGINT, SIG_DFL); // TO REM
	while (cmd && cmd->purpose != CMD_DELIM)
	{
		if (cmd->purpose == COMMAND && ft_strchr(cmd->content, '*'))
			filename_expand_it(cmd);
		cmd = cmd->next;
	}
}
