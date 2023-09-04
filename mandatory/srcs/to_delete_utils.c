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
	printf("--begin print cmd--\n");
	while(cmd != NULL && cmd->content != NULL)
	{
		printf("%s\n",cmd->content);
		cmd = cmd->next;
	}
	printf("--end print cmd--\n");
}

void	print_char_arr(char **arr)
{
	int i;

	i = 0;
	printf("--begin print cmd--\n");
	while(arr[i])
		printf("%s\n",arr[i++]);
	printf("--end print cmd--\n");
}
