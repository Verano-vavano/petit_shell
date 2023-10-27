/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:22:46 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/27 18:33:52 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

static bool	is_valid_num_arg(char *arg)
{
	while (arg && is_sign(*arg))
		arg++;
	while (arg && is_num(*arg))
		arg++;
	return (!arg || *arg == '\0');
}

int	math_errors(t_expr_ll *expr_ll, char *clean)
{
	t_expr_ll	*ptr;

	ptr = expr_ll;
	while (ptr && ptr->var_value)
	{
		if (!is_valid_num_arg(ptr->var_value)
			|| (ptr->next && !is_valid_num_arg(ptr->next->var_value)))
			return (print_special_math_error(clean, ptr));
		if (ptr->sign != NO && !ptr->next)
			return (print_math_error("operand expected", clean, ptr->index));
		if (ptr->sign == DIV && ptr->next->value == 0)
			return (print_math_error("division by 0", clean, ptr->next->index));
		if (ptr->next && ptr->sign == NO)
			return (print_math_error("syntax error in expression",
					clean, ptr->next->index));
		if (ptr->var_value == NULL && ptr->sign > 2)
			return (print_math_error("operand expected", clean, ptr->index));
		if (ptr->sign > MINUS
			&& !ptr->next->var_value && ptr->next->sign > MINUS)
			return (print_math_error("operand expected",
					clean, ptr->next->index));
		ptr = ptr->next;
	}
	return (0);
}
