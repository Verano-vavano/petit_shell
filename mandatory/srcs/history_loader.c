/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:57:13 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/03 20:17:02 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "history.h"

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
			line[ft_strlen(line) - 1] = '\0';
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
