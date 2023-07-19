/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:15:30 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/18 13:30:30 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	exit_hell(t_command *lexed)
{
	int	exit_code;
	int	i;

	if (lexed->next)
	{
		lexed = lexed->next;
		i = 0;
		while (is_dgt(lexed->content[i]))
			i++;
		if (lexed->content[i] != '\0')
		{
			printf("%s: exit: %s: numeric argument required\n",
				"Minishell", lexed->content);
			exit_code = 255;
		}
		else
			exit_code = ft_atol(lexed->content);
	}
	else
		exit_code = 0;
	exit(exit_code % 256);
}
