/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:13:48 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/06 14:32:59 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	check_syntax(char *line)
{
	int	first;
	int	meta;
	int	i;

	first = 1;
	i = 0;
	meta = 0;
	while (line[i])
	{
		if (first && is_strict_meta(line[i]))
			return (syntax_error(line + i, -1));
		if (is_metachar(line[i]) && meta == 2)
			return (syntax_error(line + i, 1));
		else if (is_metachar(line[i]))
			meta = 1;
		else if (meta && is_separator(line[i]))
			meta = 2;
		else if (meta && !is_separator(line[i]))
			meta = 0;
		first = 0;
		i++;
	}
	return (0);
}
