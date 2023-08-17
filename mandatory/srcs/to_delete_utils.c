/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_delete_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 12:24:16 by tcharanc          #+#    #+#             */
/*   Updated: 2023/08/15 12:28:00 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

void	print_lexed(t_command *lexed)
{
	const char *cmd_part[] = {
		"UNDEFINED",
		"COMMAND",
		"IN_FILE",
		"OUT_FILE",
		"HERE_DOC_DELIM",
		"OUT_FILE_APP",
		"IN_OUT_FILE",
		"HERE_STRING",
		"REDIR_ID",
		"DELIM",
		"CMD_DELIM",
		"MARKER",
		"ERROR",
	};
	printf("----\n");
	while(lexed)
	{
		printf("content = %s\n",lexed->content);
		printf("purpose = %s %d\n",cmd_part[lexed->purpose],lexed->purpose);
		printf("----\n");
		lexed = lexed->next;
	}
}
