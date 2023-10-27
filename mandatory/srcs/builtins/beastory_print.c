/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beastory_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 00:19:04 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/27 19:16:38 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	print_whole_hist(t_hist *hist)
{
	t_hist_ll	*hist_now;

	if (!hist)
		return ;
	hist_now = hist->hist_start;
	while (hist_now)
	{
		printf("%5ld\t%s\n", hist_now->num_cmd, hist_now->content);
		hist_now = hist_now->next;
	}
}

void	print_index_hist(t_hist *hist, long index)
{
	t_hist_ll	*hist_now;

	if (!hist)
		return ;
	if (index < 0)
		index = hist->len_hist + index;
	if (index > (hist->len_hist / 2))
	{
		hist_now = hist->hist_end;
		while (hist_now->num_cmd > 1 && hist_now->num_cmd != index)
			hist_now = hist_now->prev;
	}
	else
	{
		hist_now = hist->hist_start;
		while (hist_now->num_cmd < hist->len_hist && hist_now->num_cmd != index)
			hist_now = hist_now->next;
	}
	if (hist_now->num_cmd == index)
		printf("%5ld\t%s\n", index, hist_now->content);
}

int	print_range_hist(long range, t_hist *hist)
{
	t_hist_ll	*hist_now;
	long		done;

	if (range < 0)
	{
		printfd(ERR, "history %ld: invalid option\n", range);
		return (2);
	}
	else if (range == 0)
		return (0);
	done = 0;
	hist_now = hist->hist_end;
	while (done < range - 1 && hist_now)
	{
		done++;
		hist_now = hist_now->prev;
	}
	while (hist_now)
	{
		printf("%5ld\t%s\n", hist_now->num_cmd, hist_now->content);
		hist_now = hist_now->next;
	}
	return (0);
}
