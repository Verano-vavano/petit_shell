/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:31:50 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/12 22:56:16 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "history.h"

// TODO maybe redo this
char	*get_histfile(t_env *env)
{
	char	*temp_val;
	char	*histfile;
	char	*home;

	temp_val = env_getval("HISTFILE", env);
	if (!temp_val || !*temp_val || !is_file_valid(temp_val, W_OK))
	{
		histfile = rescue_tilde_funk(env);
		home = ft_strjoin(histfile, "/");
		free(histfile);
		histfile = ft_strjoin(home, STD_HISTFILE);
		free(home);
	}
	else
		histfile = ft_strdup(temp_val);
	return (histfile);
}

int	get_histsize(char *type, int stdval, t_env *env)
{
	char	*temp_val;
	int		ret;

	temp_val = env_getval(type, env);
	if (!temp_val || !(*temp_val) || !is_all_num(temp_val)
		|| ft_strlen(temp_val) > 4)
		return (stdval);
	else
	{
		ret = ft_atoi(temp_val);
		if (ret < 1)
			return (stdval);
		return (ret);
	}
	return (stdval);
}

void	remove_first_el(t_hist *hist)
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

void	add_all_hist(t_hist *hist)
{
	t_hist_ll	*hist_now;

	hist_now = hist->hist_start;
	while (hist_now && hist_now->content)
	{
		add_history(hist_now->content);
		hist_now = hist_now->next;
	}
}
