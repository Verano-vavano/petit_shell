/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:13:15 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/10 17:48:14 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

long long calculate(t_expr_ll *expr_ll)
{
	long long result;
	t_expr_ll *expr;

	result = 0;
	expr = expr_ll;
	while(expr)
	{
		if (expr->sign == PLUS)
			result = expr->value + expr->next->value;
		else if (expr->sign == MINUS)
			result = expr->value - expr->next->value;
		else if (expr->sign == DIV)
			result = expr->value / expr->next->value;
		else if (expr->sign == MULT)
			result = expr->value * expr->next->value;
		expr= expr->next->next;
	}
	return (result);
}
