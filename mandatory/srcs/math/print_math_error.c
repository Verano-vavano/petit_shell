/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_math_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:32:00 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/27 18:26:36 by hdupire          ###   ########.fr       */
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

	if (ptr->var_value && !is_all_num(ptr->var_value))
		error_token = ft_strdup(ptr->var_value);
	else
		error_token = get_error_token(&clean[ptr->index], ptr);
	if (ptr->next && ptr->next->var_value && error_token)
		printfd(STDERR_FILENO, "%s: %s: syntax error: %s (error token is \"%s\")\n",
			PROG_NAME, error_token, "Value too great for base",
			ptr->next->var_value);
	else if (error_token)
		printfd(STDERR_FILENO, "%s: %s: syntax error: %s\n",
			PROG_NAME, error_token, "Value too great for base");
	if (error_token)
		free(error_token);
	return (1);
}
