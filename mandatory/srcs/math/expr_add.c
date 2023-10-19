/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:02:52 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/19 17:03:04 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
// add newly created operation to the end of the list
// return false if there is nothing to add.
bool	expr_add(t_expr_ll *newest, t_expr_ll **expr)
{
	t_expr_ll	*last;

	if (expr && *expr)
	{
		last = expr_last(*expr);
		last->next = newest;
	}
	else
		*expr = newest;
	return (true);
}
