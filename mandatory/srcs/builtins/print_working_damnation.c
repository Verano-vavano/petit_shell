/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_working_damnation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:10:56 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/06 15:31:52 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include <unistd.h>

int	print_working_damnation(char *cwd)
{
	char	cwd_save[1024];

	if (cwd)
		printfd(STDOUT_FILENO, "%s\n", cwd);
	else if (getcwd(cwd_save, sizeof(cwd_save)) != NULL)
		printfd(STDOUT_FILENO, "%s\n", cwd_save);
	else
		printfd(STDOUT_FILENO, "getcwd error\n");
	return (0);
}