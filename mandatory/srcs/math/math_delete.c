/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:27:41 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/21 22:06:20 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO delete this file
#include "math.h"

void print_ops(t_operations_ll *ops)
{
	char *types[] = {
		"NUM",
		"OPERATOR",
	};
	t_operations_ll *ptr = ops;
	while(ptr)
	{
		printfd(STDOUT_FILENO, "Type is %s\n",types[ptr->type]);
		ptr = ptr->next;
	}
}
