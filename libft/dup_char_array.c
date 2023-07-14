/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_char_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:23:54 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/14 20:04:18 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**dup_char_array(char **arr)
{
	int	i;
	char	**ret;

	ret = malloc(sizeof(char *) * (get_char_array_size(arr) + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while(arr[++i])
		ret[i] = ft_strdup(arr[i]);
	ret[i] = NULL;
	return (ret);
}
