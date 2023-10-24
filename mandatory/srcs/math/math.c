/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:17:55 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/24 17:01:48 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include <ctype.h>

// TODO refaire le parsing pour eviter le dernier if.
static size_t	parsed_len(t_expr_ll *expr_ll, char *clean)
{
	size_t	i;

	i = expr_last(expr_ll)->index;
	while (is_digit(clean[i]) || ft_isalpha(clean[i]))
		i++;
	while (is_spc(clean[i]))
		i++;
	if (clean[i] == '-' || clean[i] == '+')
		while (clean[i] == '-' || clean[i] == '+')
			i++;
	else if (is_sign(clean[i]))
		i++;
	// Je le retire parce que ça fixe le bug ((x+y)) qui renvoit une erreur
	// Si ça bug quelque part, esssayer de le remettre
	if (i == ft_strlen(clean) - 1 && is_spc(clean[i]))
		i++;
	return (i);
}

// parse the cleaned_input into a linked list of expressions
t_expr_ll	*init_expr_ll(char *clean)
{
	t_expr_ll	*expr_ll;
	size_t		i;

	i = 0;
	expr_ll = NULL;
	while (clean[i] && expr_add(expr_create(i, clean), &expr_ll))
		i = parsed_len(expr_ll, clean);
	return (expr_ll);
}

// return true if the given input is a valid arithmetic expression.
// TODO skip command if not expanded
bool	do_math(t_command *cmd)
{
	char		*clean;
	t_expr_ll	*expr_ll;

	signal(SIGINT, SIG_DFL);
	clean = clean_input(cmd->content);
	if (!clean)
		return (false);
	expr_ll = init_expr_ll(clean);
	if (math_errors(expr_ll, clean))
		return (free_expr_ll(expr_ll), free(clean), false);
	free(cmd->content);
	cmd->content = ft_iiitoa(calculate(expr_ll));
	free(clean);
	free_expr_ll(expr_ll);
	return (true);
}
