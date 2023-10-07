/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beastory.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 23:59:35 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/07 12:18:51 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "history.h"

static void	write_it_in(t_hist_ll *hist_now, int fd)
{
	while (hist_now)
	{
		write(fd, hist_now->content, ft_strlen(hist_now->content));
		write(fd, "\n", 1);
		hist_now = hist_now->next;
	}
}

static void	write_hist_soft(t_hist *hist, t_env *env)
{
	t_hist_ll	*hist_now;
	char		*histfile;
	int			fd;
	int			histsize;
	int			index_start;

	histfile = get_histfile(env);
	if (!histfile)
		return ;
	histsize = get_histsize("HISTFILESIZE", STD_HISTFILESIZE, env);
	index_start = 1;
	if (hist->len_hist > histsize)
		index_start = hist->len_hist - histsize;
	hist_now = hist->hist_start;
	while (hist_now && hist_now->num_cmd != index_start)
		hist_now = hist_now->next;
	fd = open(histfile, O_CREAT | O_WRONLY, O_TRUNC, 0644);
	if (fd < 0)
	{
		free(histfile);
		return ;
	}
	write_it_in(hist_now, fd);
	close(fd);
	free(histfile);
}

static void	clear_hist(t_tool *tool, char **cmd)
{
	char	read_buf[1024];
	int		readed;

	if (cmd[1][1] == 'c')
	{
		printf("Do you want to clear the whole history ?");
		printf("the history file will be emptied) [y/n] > ");
		readed = read(READ, read_buf, 1023);
		if (readed == -1)
			return ;
		read_buf[readed - 1] = 0;
		if (ft_strcmp(read_buf, "y"))
			return ;
	}
	free_history(tool->hist, false);
	tool->hist->hist_start = 0;
	tool->hist->hist_end = 0;
	rl_clear_history();
}

int	beastory(char **cmd, t_tool *tool)
{
	int	ret;

	ret = 0;
	if (!cmd[1])
		print_whole_hist(tool->hist);
	else if (!ft_strcmp(cmd[1], "-c") || !ft_strcmp(cmd[1], "-C"))
		clear_hist(tool, cmd);
	else if (!ft_strcmp(cmd[1], "-i") && cmd[2] && is_long(cmd[2], true))
		print_index_hist(tool->hist, ft_atol(cmd[2]));
	else if (!ft_strcmp(cmd[1], "-w"))
		write_hist_soft(tool->hist, tool->env);
	else if (is_long(cmd[1], true))
		ret = print_range_hist(ft_atol(cmd[1]), tool->hist);
	if (ret == 2)
	{
		printfd(ERR, "usage: history: [-cC] [-d offset] or [n] or [-i offset]");
		printfd(ERR, " or [-w]\n");
	}
	return (ret);
}
