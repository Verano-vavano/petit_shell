/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_des_enfers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:54:37 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/05 21:02:32 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

int	is_arg(char *arg, int *newline)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	if (arg[i] != '\0')
		return (0);
	*newline = 0;
	return (1);
}

void	echo_des_enfers(t_command *lexed)
{
	int	newline;

	newline = 1;
	if (lexed)
	{
		while (lexed && is_arg(lexed->content, &newline))
			lexed = lexed->next;
		while (lexed)
		{
			printf("%s", lexed->content);
			if (lexed->next)
				printf(" ");
			lexed = lexed->next;
		}
	}
	if (newline)
		printf("\n");
}
