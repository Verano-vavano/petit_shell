/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_infernal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:47:35 by tcharanc          #+#    #+#             */
/*   Updated: 2023/10/25 17:55:32 by hdupire          ###   ########.fr       */
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

static void	print_env_ptr(t_env *ptr, bool exported)
{
	if (ptr->is_exported && (exported || (ptr->value)))
	{
		if (exported)
			printfd(STDOUT_FILENO, "%s", "declare -x ");
		if (exported || ptr->value)
			printfd(STDOUT_FILENO, "%s", ptr->key);
		if (ptr->value)
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
}

int	env_infernal(t_env *env, bool exported)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		print_env_ptr(ptr, exported);
		ptr = ptr->next;
	}
	return (0);
}
