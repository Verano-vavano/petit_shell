/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:46:09 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/26 17:10:47 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

t_operations_ll *assign_digit(const char *cleaned, int *i)
{
	t_operations_ll *newest;
	char	*int_str;
	int		j;
	int		k;

	j = *i;
	while(is_digit(cleaned[j]))
		j++;
	if (is_alpha(cleaned[j]))
	{
		printfd(STDERR_FILENO, "Number too big for base\n");
		return (NULL);
	}
	newest = malloc(sizeof(t_operations_ll));
	if (!newest)
		return (NULL);
	int_str = malloc(sizeof(char) * ((j - *i) + 1));
	j = *i;
	k = 0;
	while(is_digit(cleaned[j]))
		int_str[k++] = cleaned[j++];
	int_str[k] = '\0';
	newest->type = NUM;
	newest->value = ft_atoi(int_str);
	newest->index = *i;
	newest->next = NULL;
	*i = j;
	printfd(STDOUT_FILENO, "Int is = %d\n",newest->value);
	free(int_str);
	return (newest);
}

t_operations_ll *assign_operator(const char *cleaned, int *i)
{
	t_operations_ll *newest;
	char *operator_str;
	int j;
	int k;

	newest = NULL;
	j = *i;
	while(is_operator(cleaned[j]))
		j++;
	operator_str = malloc(sizeof(char) * ((j - *i) + 1));
	if (!operator_str)
		return (NULL);
	newest = malloc(sizeof(t_operations_ll));
	j = *i;
	k = 0;
	while(is_operator(cleaned[j]))
		operator_str[k++] = cleaned[j++];
	operator_str[k] = '\0';
	newest->type = OPERATOR;
	newest->op_type = find_optype(operator_str);
	newest->next = NULL;
	newest->index = *i;
	*i = j;
	return (newest);
}

t_operations_ll *assign_var(const char *cleaned, t_env *env, int *i)
{
	int j;
	int k;
	char *varname;
	t_env *env_ptr;
	t_operations_ll *newest;

	newest = NULL;
	j = *i;
	while(is_varname_char(cleaned[j]))
		j++;
	varname = malloc(sizeof(char) * ((j - *i) + 1));
	if (!varname)
		return (NULL);
	j = *i;
	k = 0;
	while (is_varname_char(cleaned[j]))
		varname[k++] = cleaned[j++];
	varname[k] = '\0';
	newest = malloc(sizeof(t_operations_ll));
	newest->next = NULL;
	newest->type = NUM;
	env_ptr = env_getptr(varname, env);
	if (!env_ptr || !*env_ptr->value)
		newest->value = 0;
	else
		newest->value = ft_atoi(env_ptr->value); // TODO Check input if it is valid.
	*i = j;
	return (newest);
}
