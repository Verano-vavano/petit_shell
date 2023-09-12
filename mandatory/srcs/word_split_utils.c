/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:25:47 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/11 19:16:45 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	search_next_ifs(char *newer, char *ifs)
{
	int	i;

	i = 0;
	while (newer[i])
	{
		if (ft_strchr(ifs, newer[i]))
			return (i);
		i++;
	}
	return (i);
}

char	*get_ifs(t_env *env)
{
	char	*ifs;
	char	*temp;

	if (env_contain("IFS", env))
	{
		temp = env_getval("IFS", env);
		if (!temp || !*temp)
			ifs = ft_calloc(1, sizeof (char));
		else
			ifs = ft_strdup(temp);
	}
	else
		ifs = ft_strdup(" \t\n");
	return (ifs);
}
