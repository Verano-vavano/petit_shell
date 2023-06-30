/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:00:27 by hdupire           #+#    #+#             */
/*   Updated: 2023/06/30 11:18:10 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	syntax_error(char *token)
{
	write(2, "Syntax error near unexpected token '", 36);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
}
