/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_expr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:03:45 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/19 17:04:09 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

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
