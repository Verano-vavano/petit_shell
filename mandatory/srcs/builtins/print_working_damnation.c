/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_working_damnation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:10:56 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/12 14:22:56 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include <unistd.h>

void	print_working_damnation()
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n",cwd);
	else
		printf("getcwd error\n");
}
