/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:27:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/05 14:42:18 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "history.h"

void	write_hist(t_hist *h, t_env *env)
{
	char		*histfile;
	int			fd;
	int			histsize;

	histfile = get_histfile(env);
	if (!histfile)
		return ;
	histsize = get_histsize("HISTFILESIZE", STD_HISTFILESIZE, env);
	while (histsize < h->len_hist)
		remove_first_el(h);
	fd = open(histfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	while (h->len_hist)
	{
		write(fd, h->hist_start->content, ft_strlen(h->hist_start->content));
		write(fd, "\n", 1);
		remove_first_el(h);
	}
	close(fd);
	free(histfile);
}

static void	add_hist_struct(t_hist *hist, char *line, int histsize)
{
	t_hist_ll	*hist_now;
	bool		first;

	first = false;
	if (hist->hist_start == 0)
	{
		first = true;
		hist->hist_start = ft_calloc(1, sizeof (t_hist_ll));
		if (hist->hist_start == 0)
			return ;
		hist->hist_end = hist->hist_start;
	}
	hist_now = hist->hist_end;
	if (!first)
	{
		hist_now->next = ft_calloc(1, sizeof (t_hist_ll));
		if (!hist_now->next)
			return ;
		hist_now = hist_now->next;
		hist->hist_end = hist->hist_end->next;
	}
	hist_now->content = ft_strdup(line);
	hist->len_hist++;
	while (hist->len_hist > histsize)
		remove_first_el(hist);
}

void	add_to_hist(t_env *env, t_hist *hist, char *line)
{
	int		histsize;
	bool	refresh;

	if (hist && hist->hist_end && hist->hist_end->content
		&& ft_strcmp(hist->hist_end->content, line) == 0)
		return ;
	histsize = get_histsize("HISTSIZE", STD_HISTSIZE, env);
	refresh = (histsize <= hist->len_hist);
	add_hist_struct(hist, line, histsize);
	add_history(line);
	if (refresh)
	{
		printf("LOL\n");
		rl_clear_history();
		add_all_hist(hist);
	}
}

static void	cpy_history(t_hist *hist, char *histfile, int histsize)
{
	int		fd;
	char	*line;

	fd = open(histfile, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		if (line && *line)
		{
			line[ft_strlen(line) - 1] = 0;
			add_hist_struct(hist, line, histsize);
		}
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

t_hist	*load_history(t_env *env)
{
	t_hist	*hist;
	char	*histfile;
	int		histsize;

	hist = ft_calloc(1, sizeof (t_hist));
	if (!hist)
		return (0);
	hist->hist_start = 0;
	histfile = get_histfile(env);
	if (!histfile)
		return (0);
	histsize = get_histsize("HISTSIZE", STD_HISTSIZE, env);
	cpy_history(hist, histfile, histsize);
	add_all_hist(hist);
	free(histfile);
	return (hist);
}
