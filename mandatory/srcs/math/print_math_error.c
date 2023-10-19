/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_math_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:32:00 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/19 17:45:33 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include <unistd.h>

int	print_math_error(char *error_msg, char *clean, int i)
{
	printfd(STDERR_FILENO, "%s: %s: syntax error: %s (error token is \"%s\")\n",
		PROG_NAME, clean, error_msg, &clean[i]);
	return (1);
}
