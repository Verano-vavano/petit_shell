/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_infernal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:47:35 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/20 13:15:24 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

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

int	env_infernal(t_env *env, bool exported)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (ptr->is_exported && (exported || (ptr->value)))
		{
			if (exported)
				printfd(STDOUT_FILENO, "%s", "declare -x ");
			printfd(STDOUT_FILENO, "%s", ptr->key);
			if (ptr->value && (exported || ptr->value[0]))
			{
				printfd(STDOUT_FILENO, "=");
				if (exported)
					printfd(STDOUT_FILENO, "\"");
				if (ptr->value[0])
					printfd(STDOUT_FILENO, "%s", ptr->value);
				if (exported)
					printfd(STDOUT_FILENO, "\"");
			}
			printfd(STDOUT_FILENO, "\n");
		}
		ptr = ptr->next;
	}
	return (0);
}
