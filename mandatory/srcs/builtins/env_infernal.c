/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_infernal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:47:35 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/14 10:31:43 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"
#include "stdarg.h"

void	print_paths(t_env *ptr)
{
	int	i;

	i = 0;
	while (ptr->value[i])
	{
		printfd(STDOUT_FILENO, "%s", ptr->value[i]);
		if (ptr->value[++i])
			printfd(STDOUT_FILENO, ":");
	}
}

int	env_infernal(t_env *env, bool export)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (ptr->is_exported && (export || (ptr->value && ptr->value[0])))
		{
			if (export)
				printfd(STDOUT_FILENO, "%s",  "declare -x ");
			printfd(STDOUT_FILENO, "%s", ptr->key);
			if (ptr->value)
			{
				printfd(STDOUT_FILENO, "=");
				if (export)
					printfd(STDOUT_FILENO, "\"");
				if (ptr->value && ptr->value[0])
					printfd(STDOUT_FILENO, "%s", ptr->value);
				if (export)
					printfd(STDOUT_FILENO, "\"");
			}
			printfd(STDOUT_FILENO, "\n");
		}
		ptr = ptr->next;
	}
	return (0);
}
