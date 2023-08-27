/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:27:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/27 13:16:45 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

#define STD_HISTFILE ".shellpt_history"
#define STD_HISTSIZE 500
#define STD_HISTFILESIZE 500

static void	remove_first_el(t_hist *hist)
{
	t_hist_ll	*next;

	if (!hist->hist_start)
		return ;
	next = hist->hist_start->next;
	if (hist->hist_start->content)
		free(hist->hist_start->content);
	free(hist->hist_start);
	hist->hist_start = next;
	hist->len_hist--;
}

void	free_history(t_hist *hist)
{
	while (hist->len_hist)
		remove_first_el(hist);
	free(hist);
}

void	write_hist(t_hist *hist, t_env *env)
{
	char		*histfile;
	char		*home;
	char		**temp_val;
	int			fd;
	int			histsize;

	temp_val = env_getval("HISTFILE", env);
	if (!temp_val || !(*temp_val) || !is_file_valid(*temp_val, W_OK))
	{
		histfile = rescue_tilde_funk(env);
		home = ft_strjoin(histfile, "/");
		free(histfile);
		histfile = ft_strjoin(home, STD_HISTFILE);
		free(home);
	}
	else
		histfile = ft_strdup(*temp_val);
	if (!histfile)
		return ;
	temp_val = env_getval("HISTFILESIZE", env);
	if (!temp_val || !(*temp_val) || !is_all_num(*temp_val) || ft_strlen(*temp_val) > 4)
		histsize = STD_HISTSIZE;
	else
	{
		histsize = ft_atoi(*temp_val);
		if (histsize < 1)
			histsize = STD_HISTSIZE;
	}
	while (histsize < hist->len_hist)
		remove_first_el(hist);
	fd = open(histfile, O_WRONLY);
	if (fd < 0)
		return ;
	while (hist->len_hist)
	{
		write(fd, hist->hist_start->content, ft_strlen(hist->hist_start->content));
		write(fd, "\n", 1);
		remove_first_el(hist);
	}
	close(fd);
	free(histfile);
}

static void	add_all_hist(t_hist *hist)
{
	t_hist_ll	*hist_now;

	hist_now = hist->hist_start;
	while (hist_now && hist_now->content)
	{
		add_history(hist_now->content);
		hist_now = hist_now->next;
	}
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
	}
	hist_now->content = line;
	hist->hist_end = hist_now;
	hist->len_hist++;
	while (hist->len_hist > histsize)
		remove_first_el(hist);
}

void	add_to_hist(t_env *env, t_hist *hist, char *line)
{
	int		histsize;
	bool	refresh;
	char	**temp_val;

	temp_val = env_getval("HISTSIZE", env);
	if (!temp_val || !(*temp_val) || !is_all_num(*temp_val) || ft_strlen(*temp_val) > 4)
		histsize = STD_HISTSIZE;
	else
	{
		histsize = ft_atoi(*temp_val);
		if (histsize < 1)
			histsize = STD_HISTSIZE;
	}
	refresh = (histsize == hist->len_hist);
	add_hist_struct(hist, line, histsize);
	add_history(line);
	if (refresh)
	{
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
		else if (line && !(*line))
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

t_hist	*load_history(t_env *env)
{
	t_hist	*hist;
	char	**temp_val;
	char	*histfile;
	char	*home;
	int		histsize;

	hist = ft_calloc(1, sizeof (hist));
	if (!hist)
		return (0);
	temp_val = env_getval("HISTFILE", env);
	if (!temp_val || !(*temp_val) || !is_file_valid(*temp_val, R_OK))
	{
		histfile = rescue_tilde_funk(env);
		home = ft_strjoin(histfile, "/");
		free(histfile);
		histfile = ft_strjoin(home, STD_HISTFILE);
		free(home);
	}
	else
		histfile = ft_strdup(*temp_val);
	temp_val = env_getval("HISTSIZE", env);
	if (!temp_val || !(*temp_val) || !is_all_num(*temp_val) || ft_strlen(*temp_val) > 4)
		histsize = STD_HISTSIZE;
	else
	{
		histsize = ft_atoi(*temp_val);
		if (histsize < 1)
			histsize = STD_HISTSIZE;
	}
	cpy_history(hist, histfile, histsize);
	add_all_hist(hist);
	free(histfile);
	return (hist);
}
