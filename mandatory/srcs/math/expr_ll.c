/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_ll.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:19:22 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/10 16:19:59 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include <stdint.h>
#include <unistd.h>

// get last operation.
t_expr_ll *expr_last(t_expr_ll *expr_ll)
{
	if (!expr_ll)
		return (NULL);
	while (expr_ll->next != NULL)
		expr_ll = expr_ll->next;
	return (expr_ll);
}

// TODO maybe delete this?
// this is needed by expr_create
static Sign sign_determine(char c)
{
	if (c == '+')
		return(PLUS);
	else if (c == '-')
		return (MINUS);
	else if (c == '/')
		return (DIV);
	else if (c == '*')
		return (MULT);
	return (NO);
}

// Create a new expression link.
// for that parse the string
t_expr_ll *expr_create(int i, char *clean, t_env *env)
{
	(void)env;
	t_expr_ll	*created;
	intmax_t	j;

	created = malloc(sizeof(t_expr_ll));
	if (!created)
		return (NULL);
	*created = (t_expr_ll){ .value = 0, .var_name = NULL, .var_value = NULL,
		.index = 0, .sign = NO, .next = NULL };
	while (is_spc(clean[i]))
		i++;
	if (clean[i])
	{
		// TODO handle basic errors first char.
		created->index = i;
		j = i;
		while (is_digit(clean[j]))
			j++;
		created->var_value = malloc(sizeof(char) * (j - i + 1));
		j = 0;
		while(is_digit(clean[i]))
			created->var_value[j++] = clean[i++];
		created->var_value[j] = '\0';
		created->value = ft_atoiii(created->var_value);
		if (!clean[i])
			return (created);
		while(clean[i] && is_spc(clean[i]))
			i++;
		created->sign = sign_determine(clean[i]);
	}
	return (created);
}

// add newly created operation to the end of the list
// return false if there is nothing to add.
bool expr_add(t_expr_ll *newest, t_expr_ll **expr)
{
	t_expr_ll *last;

	if (expr && *expr)
	{
		last = expr_last(*expr);
		last->next = newest;
	}
	else
		*expr = newest;
	return (true);
}

void	free_expr(t_expr_ll *expr)
{
	if (expr)
	{
		if (expr->var_name)
			free(expr->var_name);
		if (expr->var_value)
			free(expr->var_value);
	}
	free(expr);
}

void	free_expr_ll(t_expr_ll *expr_ll)
{
	t_expr_ll	*ptr;
	t_expr_ll	*next;

	ptr = expr_ll;
	while (ptr)
	{
		next = ptr->next;
		free_expr(ptr);
		ptr = next;
	}
	expr_ll = NULL;
}
