/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fe_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:00:59 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/06 16:21:15 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	get_path_star_fe(char *cnt)
{
	char	quoted;
	int		i;
	int		last_s;

	i = 0;
	last_s = -1;
	quoted = 0;
	while (cnt[i] && (quoted || (cnt[i] != '*' && cnt[i] != '?')))
	{
		quoted = is_quoted(cnt, i, quoted);
		if (cnt[i] == '/' && !quoted)
			last_s = i;
		i++;
	}
	if (last_s == -1)
		return (i);
	return (last_s);
}

char	*ft_strstr_fe(char *haystack, char *needle)
{
	int		i;
	int		j;
	bool	found;

	i = -1;
	while (haystack[++i])
	{
		if (haystack[i] == needle[0] || needle[0] == '?')
		{
			found = true;
			j = 0;
			while (haystack[i + j] && needle[j])
			{
				if (needle[j] != '?' && needle[j] != haystack[i + j])
				{
					found = false;
					break ;
				}
				j++;
			}
			if (found && !needle[j])
				return (haystack + i);
		}
	}
	return (0);
}

bool	not_over(char *s)
{
	int	j;

	j = 0;
	if (s[j] != '*')
		return (false);
	j++;
	while (s[j] && s[j] != '/')
	{
		if (s[j] == '*')
			return (true);
		j++;
	}
	return (false);
}

int	move_end_stars(char *qmat)
{
	int	i;

	i = 0;
	while (qmat[i] == '*')
		i++;
	return (i);
}
