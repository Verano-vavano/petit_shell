/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_ll.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:19:22 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/21 11:43:09 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include <stdint.h>
#include <unistd.h>

// TODO maybe delete this?
// this is needed by expr_create
static t_sign	sign_determine(char c)
{
	if (c == '+')
		return (PLUS);
	else if (c == '-')
		return (MINUS);
	else if (c == '/')
		return (DIV);
	else if (c == '*')
		return (MULT);
	return (NO);
}

static t_sign	sign_neg_or_pos(char *clean)
{
	int	i;
	int	neg_count;

	i = 0;
	neg_count = 0;
	while (clean[i] && (clean[i] == '-' && clean[i] == '+'))
		if (clean[i] == '-')
			neg_count++;
	if (neg_count % 2)
		return (PLUS);
	return (MINUS);
}

static void	fill_created(t_expr_ll *created, char *clean, int i)
{
	intmax_t	j;

	created->index = i;
	j = i;
	while (is_digit(clean[j]))
		j++;
	if (j > i)
	{
		created->var_value = malloc(sizeof(char) * (j - i + 1));
		j = 0;
		while (is_digit(clean[i]))
			created->var_value[j++] = clean[i++];
		created->var_value[j] = '\0';
		created->value = ft_atoiii(created->var_value);
	}
	if (!clean[i])
		return ;
	while (clean[i] && is_spc(clean[i]))
		i++;
	if (clean[i] == '-' || clean[i] == '+')
		created->sign = sign_neg_or_pos(&clean[i]);
	else
		created->sign = sign_determine(clean[i]);
}

// Create a new expression link.
// for that parse the string
t_expr_ll	*expr_create(int i, char *clean, t_env *env)
{
	t_expr_ll	*created;

	(void)env;
	created = malloc(sizeof(t_expr_ll));
	if (!created)
		return (NULL);
	*created = (t_expr_ll){.value = 0, .var_name = NULL, .var_value = NULL,
		.index = 0, .sign = NO, .next = NULL };
	while (is_spc(clean[i]))
		i++;
	if (clean[i])
		fill_created(created, clean, i);
	return (created);
}
