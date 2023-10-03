/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:27:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/03 20:13:52 by hdupire          ###   ########.fr       */
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

static bool	create_hist_ll(t_hist *hist)
{
	if (hist->hist_start == NULL)
	{
		hist->hist_start = ft_calloc(1, sizeof (t_hist_ll));
		if (hist->hist_start == NULL)
			return (true);
		hist->hist_end = hist->hist_start;
		return (true);
	}
	return (false);
}

void	add_hist_struct(t_hist *hist, char *line, int histsize)
{
	t_hist_ll	*hist_now;
	bool		first;
	long		last_num;

	first = create_hist_ll(hist);
	last_num = 0;
	if (!hist->hist_start)
		return ;
	hist_now = hist->hist_end;
	if (!first)
	{
		last_num = hist_now->num_cmd;
		hist_now->next = ft_calloc(1, sizeof (t_hist_ll));
		if (!hist_now->next)
			return ;
		hist_now->next->prev = hist_now;
		hist_now = hist_now->next;
		hist->hist_end = hist->hist_end->next;
	}
	hist_now->content = ft_strdup(line);
	if (last_num != LONG_MAX)
		hist_now->num_cmd = last_num + 1;
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
	refresh = (hist && histsize <= hist->len_hist);
	add_hist_struct(hist, line, histsize);
	add_history(line);
	if (refresh)
	{
		rl_clear_history();
		add_all_hist(hist);
	}
}
