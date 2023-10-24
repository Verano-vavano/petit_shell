/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 10:27:16 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/24 18:23:53 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"
#include "shellpticflesh.h"
#include <stddef.h>

static bool	is_ignore_char(char c)
{
	return (c == '\n' || c == '"' || c == '$');
}

char	*clean_input(const char *input)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*clean;

	len = ft_strlen(input) - 5;
	i = 2;
	j = 0;
	while (input[++i])
		if (is_ignore_char(input[i]))
			len--;
	clean = ft_calloc(sizeof (char), len + 1);
	if (!clean)
		return (NULL);
	i = 2;
	while (input[++i] && j < len)
		if (!is_ignore_char(input[i]))
			clean[j++] = input[i];
	clean[j] = '\0';
	return (clean);
}
