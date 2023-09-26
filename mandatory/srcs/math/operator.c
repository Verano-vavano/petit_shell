/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:48:12 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/21 21:51:41 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

Operator find_optype(const char *operator_str)
{
	if (ft_strcmp(operator_str, "+") == 0)
		return (ADDITION);
	else if (ft_strcmp(operator_str, "-") == 0)
		return (SUBSTRACTION);
	else if (ft_strcmp(operator_str, "*") == 0)
		return (MULTIPLICATION);
	else if (ft_strcmp(operator_str, "/") == 0)
		return (DIVISION);
	else if (ft_strcmp(operator_str, "%") == 0)
		return (REMAINDER);
	else if (ft_strcmp(operator_str, "~") == 0)
		return (BITWISE_NEG);
	else if (ft_strcmp(operator_str, "&") == 0)
		return (BITWISE_AND);
	else if (ft_strcmp(operator_str, "^") == 0)
		return (BITWISE_OR);
	else if (ft_strcmp(operator_str, "<<") == 0)
		return (BITSHIFT_LEFT);
	else if (ft_strcmp(operator_str, ">>") == 0)
		return (BITSHIFT_RIGHT);
	else if (ft_strcmp(operator_str, "**") == 0)
		return (EXPONENTIAL);
	else if (ft_strcmp(operator_str, ">") == 0)
		return (COMP_SUP);
	else if (ft_strcmp(operator_str, ">=") == 0)
		return (COMP_SUP_EQ);
	else if (ft_strcmp(operator_str, "<") == 0)
		return (COMP_INF);
	else if (ft_strcmp(operator_str, "<=") == 0)
		return (COMP_INF_EQ);
	else if (ft_strcmp(operator_str, "!") == 0)
		return (LOGIC_NEG);
	else if (ft_strcmp(operator_str, "==") == 0)
		return (EQUALITY);
	else if (ft_strcmp(operator_str, "!=") == 0)
		return (INEQUALITY);
	else if (ft_strcmp(operator_str, "&&") == 0)
		return (LOGIC_AND);
	else if (ft_strcmp(operator_str, "||") == 0)
		return (LOGIC_OR);
	else if (ft_strcmp(operator_str, ",") == 0)
		return (ASSIGNEMENTS);
	// TODO handle post/pre incrementation
	else if (ft_strcmp(operator_str, "a++") == 0)
		return (POST_INCR);
	else if (ft_strcmp(operator_str, "a--") == 0)
		return (POST_DECR);
	else if (ft_strcmp(operator_str, "++a") == 0)
		return (PRE_INCR);
	else if (ft_strcmp(operator_str, "--a") == 0)
		return (PRE_DECR);
	// TODO handle ternary
	// TODO Conditional operators
	else
	    return (UNDEF);
}
