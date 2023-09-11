/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to-delete-utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:49:19 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/04 17:55:28 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shellpticflesh.h"

void	print_cmd(t_command *cmd)
{
	printfd(STDOUT_FILENO, "--begin print cmd--\n");
	while(cmd != NULL && cmd->content != NULL)
	{
		printfd(STDOUT_FILENO, "%s\n",cmd->content);
		cmd = cmd->next;
	}
	printfd(STDOUT_FILENO, "--end print cmd--\n");
}

void	print_char_arr(char **arr)
{
	int i;

	i = 0;
	printfd(STDOUT_FILENO, "--begin print cmd--\n");
	while(arr[i])
		printfd(STDOUT_FILENO, "%s\n",arr[i++]);
	printfd(STDOUT_FILENO, "--end print cmd--\n");
}