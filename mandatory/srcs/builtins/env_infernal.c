/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_infernal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:47:35 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/11 15:59:12 by tcharanc         ###   ########.fr       */
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

static void	print_ptr(t_env *ptr)
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

int	env_infernal(t_env *env, ...)
{
	t_env	*ptr;
	char	*prepend;
	va_list	list;

	ptr = env;
	va_start(list, env);
	prepend = va_arg(list, char *);
	while (ptr)
	{
		if (ptr->is_exported && (prepend || (ptr->value && ptr->value[0])))
		{
			if (prepend != NULL)
				printfd(STDOUT_FILENO, "%s", prepend);
			printfd(STDOUT_FILENO, "%s", ptr->key);
			if (ptr->value)
				printfd(STDOUT_FILENO, "=");
			if (ptr->value && prepend)
				printfd(STDOUT_FILENO, "\"");
			if (ptr->value)
				print_ptr(ptr);
			if (ptr->value && prepend)
				printfd(STDOUT_FILENO, "\"");
			printfd(STDOUT_FILENO, "\n");
		}
		ptr = ptr->next;
	}
	return (0);
}
