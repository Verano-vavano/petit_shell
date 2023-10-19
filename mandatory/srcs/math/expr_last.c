/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_last.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:00:57 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/19 17:01:06 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
// get last operation.
t_expr_ll	*expr_last(t_expr_ll *expr_ll)
{
	if (!expr_ll)
		return (NULL);
	while (expr_ll->next != NULL)
		expr_ll = expr_ll->next;
	return (expr_ll);
}
