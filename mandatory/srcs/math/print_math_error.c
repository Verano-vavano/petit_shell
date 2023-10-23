/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_math_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:32:00 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/23 17:50:50 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"
#include "shellpticflesh.h"
#include <unistd.h>

int	print_math_error(char *error_msg, char *clean, int i)
{
	printfd(STDERR_FILENO, "%s: %s: syntax error: %s (error token is \"%s\")\n",
		PROG_NAME, clean, error_msg, &clean[i]);
	return (1);
}

static char	*get_error_token(char *error_beginning, t_expr_ll *ptr)
{
	int		len;
	int		i;
	char	*error_token;

	len = (ptr->next->index - ptr->index) + ft_strlen(ptr->next->var_value);
	error_token = malloc(len * sizeof(char));
	if (!error_token)
		return (NULL);
	i = -1;
	while (++i < len)
		error_token[i] = error_beginning[i];
	error_token[i] = '\0';
	return (error_token);
}

int	print_special_math_error(char *clean, t_expr_ll *ptr)
{
	char	*error_token;

	if (!is_all_num(ptr->var_value))
		error_token = ptr->var_value;
	else
		error_token = get_error_token(&clean[ptr->index], ptr);
	printfd(STDERR_FILENO, "%s: %s: syntax error: %s (error token is \"%s\")\n",
		PROG_NAME, error_token, "Value too great for base",
		ptr->next->var_value);
	if (error_token)
		free(error_token);
	return (1);
}
