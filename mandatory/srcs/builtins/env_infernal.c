/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_infernal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:47:35 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/05 16:19:51 by hdupire          ###   ########.fr       */
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
		printf("%s", ptr->value[i]);
		if (ptr->value[++i])
			printf(":");
	}
}

static void	print_ptr(t_env *ptr)
{
	int	i;

	i = 0;
	while (ptr->value[i])
	{
		printf("%s", ptr->value[i]);
		if (ptr->value[++i])
			printf(":");
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
				printf("%s", prepend);
			printf("%s", ptr->key);
			if (ptr->value)
				printf("=");
			if (ptr->value && prepend)
				printf("\"");
			if (ptr->value)
				print_ptr(ptr);
			if (ptr->value && prepend)
				printf("\"");
			printf("\n");
		}
		ptr = ptr->next;
	}
	return (0);
}
