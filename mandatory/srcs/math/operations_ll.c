/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_ll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:47:05 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/20 17:39:26 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include <unistd.h>

t_operations_ll *operation_last(t_operations_ll *ops)
{
	if (!ops)
		return (ops);
	while (ops->next != NULL)
		ops = ops->next;
	return (ops);
}

void operation_add(t_operations_ll *newest, t_operations_ll **ops)
{
	t_operations_ll *tmp;

	if (ops && *ops)
	{
		tmp = operation_last(*ops);
		tmp->next = newest;
	}
	else
		*ops = newest;
}
