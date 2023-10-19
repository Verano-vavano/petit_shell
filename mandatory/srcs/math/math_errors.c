/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:22:46 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/19 17:59:07 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include <unistd.h>

int	math_errors(t_expr_ll *expr_ll, char *clean)
{
	t_expr_ll	*ptr;

	printfd(STDOUT_FILENO, "bonjour\n");
	ptr = expr_ll;
	while (ptr)
	{
		if (ptr->sign != NO && !ptr->next)
			return (print_math_error("operand expected", clean, ptr->index));
		if (ptr->sign == DIV && ptr->next->value == 0)
			return (print_math_error("division by 0", clean, ptr->next->index));
		if (ptr->next && ptr->sign == NO)
			return (print_math_error("syntax error in expression",
					clean, ptr->next->index));
		ptr = ptr->next;
	}
	return (0);
}
