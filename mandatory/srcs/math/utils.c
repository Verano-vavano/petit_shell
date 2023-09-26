/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:48:48 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/21 21:48:54 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

bool print_math_error(char *input, char *error_message, int error_index) 
{
	printfd(STDOUT_FILENO, "%s: %s: %s (error token is \"%s\")\n", PROG_NAME, input, error_message, &input[error_index]);
	return (false);
}
