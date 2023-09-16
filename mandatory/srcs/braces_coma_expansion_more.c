/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_coma_expansion_more.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:24:09 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/16 13:26:49 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	find_end(char *s)
{
	int	i;
	int	in_braces;
	int	quoted;

	i = 0;
	in_braces = 0;
	quoted = 0;
	while (s[i])
	{
		quoted = is_quoted(s, i, quoted);
		if (!quoted && s[i] == '{' && (i == 0 || s[i - 1] != '\\'))
			in_braces++;
		else if (!quoted && (s[i] == '}' || s[i] == ',') && !in_braces)
			break ;
		else if (!quoted && s[i] == '}' && (i == 0 || s[i - 1] != '\\'))
			in_braces--;
		i++;
	}
	return (i);
}

char	*get_braces_ext(int *se, int *nodes, char *org)
{
	char	*temp;
	char	*temp2;
	char	*temp3;

	temp = ft_strndup(org, ft_strchr_int(org, '{'));
	if (!temp)
		return (0);
	temp2 = ft_strndup(org + nodes[1] + 1, find_end(org + nodes[1] + 1));
	if (!temp2)
	{
		free(temp);
		return (0);
	}
	temp3 = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	if (!temp3)
		return (0);
	temp = ft_strjoin(temp3, org + se[1] + 1);
	free(temp3);
	return (temp);
}
