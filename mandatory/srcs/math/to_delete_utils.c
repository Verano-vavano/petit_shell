/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 10:48:30 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/15 10:50:26 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include <unistd.h>

// Print the whole expression
void	print_expr(t_expr_ll *expr)
{
	printf("value = %lld\n", expr->value);
	if (expr->var_name != NULL)
		printf("var_name = %s\n", expr->var_name);
	if (expr->var_value != NULL)
		printf("var_value = %s\n", expr->var_value);
	printf("given sign = %d\n", expr->sign);
	printf("index = %ld\n", expr->index);
	printf("Sign = %d\n", expr->sign);
}

void	print_all_exprs(t_expr_ll *expr)
{
	t_expr_ll	*ptr;
	int			i;

	if (!expr)
		return ;
	i = 0;
	ptr = expr;
	while (1)
	{
		printfd(STDOUT_FILENO, "---elem %d---\n", i);
		print_expr(ptr);
		printfd(STDOUT_FILENO, "------\n");
		printfd(STDOUT_FILENO, "------\n");
		if (ptr->next == NULL)
			break ;
		ptr = ptr->next;
		i++;
	}
}
