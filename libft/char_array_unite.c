/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_array_unite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:59:32 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/04 18:18:40 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// function to unite a char array into one single char *
// as we use it inside minishellm put ':' between each values
// TODO Fix leak
#include "libft.h"
char	*char_array_unite(char **arr)
{
	char *ret;
	int i;
	int size;
	int j;
	int k;
	
	size = 0;
	i = -1;
	while(arr[++i])
		size += ft_strlen(arr[i]);
	size += get_char_array_size(arr);
	//size++;
	ret = malloc(sizeof(char) * size);
	i = -1;
	k = -1;
	while(arr[++i])
	{
		j = -1;
		while(arr[i][++j])
			ret[++k] = arr[i][j];
		if (arr[i + 1])
			ret[++k] = ':';
	}
	ret[++k] = '\0';
	return (ret);
}
