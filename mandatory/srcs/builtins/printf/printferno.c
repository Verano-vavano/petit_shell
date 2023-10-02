/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printferno.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 03:58:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/02 02:41:32 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include "printf.h"

bool	is_valid_format(char c, t_printf_flags *flags)
{
	if (c == 'c' || c == 's'
		|| c == 'd' || c == 'i'
		|| c == 'x' || c == 'X')
	{
		flags->format = c;
		return (true);
	}
	return (false);
}

int	printferno(char **cmd)
{
	char	*main_string;
	int		ret;

	main_string = ft_strdup(cmd[1]);
	if (main_string == NULL)
	{
		printfd(ERR, "printf: usage: printf format [arguments]\n");
		return (2);
	}
	cmd += 2;
	main_string = escape_characters(main_string);
	ret = printf_loop(cmd, main_string);
	return (ret);
}
