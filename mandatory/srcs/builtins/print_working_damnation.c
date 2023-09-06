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
		printf("%s\n", cwd);
	else if (getcwd(cwd_save, sizeof(cwd_save)) != NULL)
		printf("%s\n", cwd_save);
	else
		printf("getcwd error\n");
	return (0);
}
