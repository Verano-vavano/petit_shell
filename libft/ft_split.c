/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:12:27 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/06 15:24:08 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_word(const char *s, char c)
{
	size_t	i;
	size_t	j;
	char	*word;

	i = 0;
	j = 0;
	while (s[i] != c && s[i])
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (word == 0)
		return (0);
	while (s[j] != c && s[j])
	{
		word[j] = s[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			while (s[i] != c && s[i])
				i++;
			count++;
		}
		while (s[i] == c && s[i])
			i++;
	}
	return (count);
}

static void	ft_free_list(char **l)
{
	int	i;

	i = 0;
	while (l[i])
	{
		free(l[i]);
		i++;
	}
	free(l);
}

static int	add_word_list(char **list, char const *s, int *iter, char c)
{
	list[iter[0]] = create_word(s + iter[1], c);
	if (list[iter[0]] == 0)
	{
		ft_free_list(list);
		return (1);
	}
	iter[0]++;
	while (s[iter[1]] != c && s[iter[1]])
		iter[1]++;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	int		iter[2];

	iter[0] = 0;
	iter[1] = 0;
	list = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (list == 0)
		return (0);
	while (s[iter[1]])
	{
		if (s[iter[1]] != c && s[iter[1]])
		{
			if (add_word_list(list, s, iter, c))
				return (0);
		}
		while (s[iter[1]] == c && s[iter[1]])
			iter[1]++;
	}
	list[iter[0]] = 0;
	return (list);
}
