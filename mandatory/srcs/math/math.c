/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:17:55 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/24 22:10:16 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include <ctype.h>

// TODO refaire le parsing pour eviter le dernier if.
static size_t	parsed_len(t_expr_ll *expr_ll, char *clean)
{
	size_t	i;

	i = expr_last(expr_ll)->index;
	while (is_sign(clean[i]))
		i++;
	while (is_digit(clean[i]) || ft_isalpha(clean[i]))
		i++;
	while (is_spc(clean[i]))
		i++;
	if (clean[i] == '-' || clean[i] == '+')
		while (clean[i] == '-' || clean[i] == '+' || is_spc(clean[i]))
			i++;
	else if (is_sign(clean[i]))
		i++;
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

static size_t	get_start(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$' && cmd[i + 1] == '(' && cmd[i + 2] == '(')
			return (i);
		i++;
	}
	return (0);
}

static size_t	get_end(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ')' && cmd[i + 1] == ')')
			return (i);
		i++;
	}
	return (0);
}

static bool insert_math(t_command *cmd, char *output, size_t i_start, size_t i_end)
{
	char	*temp;

	temp = ft_strreplace(cmd->content, i_start, i_end - i_start + 2, output);
	if (!temp)
		return (true);
	free(cmd->content);
	cmd->content = temp;
	return (true);
}

// return true if the given input is a valid arithmetic expression.
// TODO skip command if not expanded
bool	do_math(t_command *cmd)
{
	char		*clean;
	t_expr_ll	*expr_ll;
	size_t		i_start;
	size_t		i_end;
	char		*output;

	signal(SIGINT, SIG_DFL);
	i_start = get_start(cmd->content);
	i_end = get_end(cmd->content);
	clean = clean_input(cmd->content, i_start, i_end);
	if (!clean)
		return (false);
	expr_ll = init_expr_ll(clean);
	if (math_errors(expr_ll, clean))
		return (free_expr_ll(expr_ll), free(clean), false);
	output = ft_iiitoa(calculate(expr_ll));
	free(clean);
	free_expr_ll(expr_ll);
	return (insert_math(cmd, output, i_start, i_end));
}
