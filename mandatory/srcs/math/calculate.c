/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:13:15 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/24 15:10:49 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include <unistd.h>

void	actualize_ll(t_expr_ll *curr_expr)
{
	t_expr_ll	*next_expr;

	curr_expr->sign = curr_expr->next->sign;
	next_expr = curr_expr->next->next;
	free_expr(curr_expr->next);
	curr_expr->next = next_expr;
}

bool	resolved_priority(t_expr_ll *expr_ll)
{
	t_expr_ll	*ptr;

	ptr = expr_ll;
	while (ptr->next)
	{
		if (ptr->sign == MULT || ptr->sign == DIV)
		{
			if (ptr->sign == MULT)
				ptr->value = ptr->value * ptr->next->value;
			else
				ptr->value = ptr->value / ptr->next->value;
			actualize_ll(ptr);
			return (true);
		}
		ptr = ptr->next;
	}
	return (false);
}

long long	calculate(t_expr_ll *expr_ll)
{
	t_expr_ll	*ptr;

	while (1)
		if (!resolved_priority(expr_ll))
			break ;
	ptr = expr_ll;
	while (ptr->next)
	{
		if (ptr->sign == PLUS)
			ptr->value = ptr->value + ptr->next->value;
		else
			ptr->value = ptr->value - ptr->next->value;
		actualize_ll(ptr);
	}
	return (ptr->value);
}
