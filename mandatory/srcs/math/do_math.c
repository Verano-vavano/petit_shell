/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:14:47 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/26 20:52:02 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"
#include "shellpticflesh.h"
#include <ctype.h>
#include <unistd.h>

t_operations_ll *operations_init(const char *cleaned, t_env *env)
{
	t_operations_ll *operations;
	t_operations_ll *tmp;
	int i;

	operations = NULL;
	if (!cleaned || !*cleaned)
		return (operations);
	i = 0;
	while(cleaned[i])
	{
		tmp = NULL;
		if (is_spc(cleaned[i]))
		{
			i++;
			continue ;
		}
		else if (is_digit(cleaned[i]))
			tmp = assign_digit(cleaned, &i);
		else if (is_operator(cleaned[i]))
			tmp = assign_operator(cleaned, &i);
		else if  (is_varname_char(cleaned[i]), &i)
			tmp = assign_var(cleaned, env, &i);
		if (!tmp)
		    return (NULL);
		else
		    operation_add(tmp, &operations);
		if (!cleaned[i])
			break ;
	}
	(void)env;
	return (operations);
}

static bool valid_ops(t_operations_ll *ops, char *input)
{
	t_operations_ll *ptr;
	Token_type prev_type;

	ptr = ops;
	if (ptr->type == OPERATOR)
	{
		printfd(STDERR_FILENO, "Beginning with an Operator");
		return (false);
	}
	prev_type = ptr->type;
	ptr = ptr->next;
	while(ptr)
	{
		if (prev_type == ptr->type)
		{
			printfd(STDERR_FILENO, "Erreur.. deux token du meme type qui se suivent\n");
			return (false);
		}
		else
			prev_type = ptr->type;
		if (!ptr->next)
			break ;
		ptr = ptr->next;
	}
	if (prev_type == OPERATOR)
		return (print_math_error(input, "syntax error: operand expected", ptr->index));
	return (true);
}

static char *calculate(t_operations_ll *operations)
{
	// TODO understand max int len in arith exp in bash
	// is it cpu dependent?
	// for sur int is too little of a type
	int result;
	t_operations_ll *ptr;
	int left;
	int right;

	ptr = operations;
	result = 0;
	while(ptr)
	{
		left = ptr->value;
		ptr = ptr->next;
		right = ptr->next->value;
		if (ptr->op_type == ADDITION)
			result += (left + right);
		else if (ptr->op_type == SUBSTRACTION)
			result -= (left - right);
		else if (ptr->op_type == MULTIPLICATION)
			result += (left * right);
		else if  (ptr->op_type == DIVISION)
			result += (left / right);
		// TODO gere que une seule operation pour le moment
		break ;
	}
	return (ft_itoa(result));
}

// return true or false depending on expension
// if no expansion
//   the calling command should be cancelled
// if expanded
//   baseline return = 0;
bool do_math(t_command *cmd, t_env *env)
{
	char *input;
	t_operations_ll *operations;

	input = clean_input(cmd->content);
	operations = operations_init(input, env);
	if (!operations)
		return (false);
	print_ops(operations);
	if (!valid_ops(operations, input))
		return (false);
	char *result = calculate(operations);
	printfd(STDOUT_FILENO, "result is %s\n", result);
	// TODO assign result to cmd
	free(result);
	free(operations);
	free(input);
	return (true);
}
