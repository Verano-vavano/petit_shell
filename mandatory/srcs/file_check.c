/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:02:02 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/02 16:02:04 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static bool	move_to_next(char *qr_match, char *file, int *i, int *j)
{
	char	*cpy;
	char	*finder;

	cpy = ft_strndup(qr_match + *j + 1, ft_strchr_int(qr_match + *j + 1, '*'));
	if (cpy)
	{
		finder = ft_strstr_fe(file + *i, cpy);
		(*j)++;
		if (finder)
			(*i) += (finder - (file + *i));
		else
			(*i) = -1;
		free(cpy);
		return (true);
	}
	(*i)++;
	(*j)++;
	return (true);
}

static bool	check_end(char *qr_match, char *file)
{
	int	i;
	int	j;

	i = ft_strlen(file) - 1;
	j = ft_strchr_int(qr_match, '/') - 1;
	while (qr_match[j] != '*')
	{
		if (i < 0)
			return (false);
		if (qr_match[j] != file[i] && qr_match[j] != '?')
			return (false);
		i--;
		j--;
	}
	return (true);
}

static int	file_check_loop(char *file, char *qmat, int *i)
{
	int	ret;

	while (file[i[0]] && qmat[i[1]] && !(qmat[i[1]] == '/'))
	{
		if (not_over(qmat + i[1]) && move_to_next(qmat, file, i, i + 1))
			continue ;
		else if (qmat[i[1]] == '*')
		{
			ret = check_end(qmat + i[1], file + i[0]);
			free(qmat);
			return (ret);
		}
		if (i[0] == -1 || (qmat[i[1]] != '/' && qmat[i[1]] != '?'
				&& qmat[i[1]] != file[*i]) || (qmat[i[1]] == '/' && file[*i]))
		{
			free(qmat);
			return (false);
		}
		i[0]++;
		i[1]++;
	}
	return (-1);
}

bool	is_valid_fe(char *file, char *matcher)
{
	int		i[2];
	int		ret;
	char	*qmat;

	i[0] = 0;
	i[1] = 0;
	qmat = quote_removal(ft_strdup(matcher));
	if (!qmat || ((qmat[0] == '*' || qmat[0] == '?') && file[0] == '.'))
	{
		if (qmat)
			free(qmat);
		return (false);
	}
	ret = file_check_loop(file, qmat, i);
	if (ret != -1)
		return (ret);
	i[1] += move_end_stars(qmat + i[1]);
	ret = ((!qmat[i[1]] || qmat[i[1]] == '/') && !file[i[0]]);
	free(qmat);
	return (ret);
}
