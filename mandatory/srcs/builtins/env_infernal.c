/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_infernal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:47:35 by tcharanc          #+#    #+#             */
/*   Updated: 2023/08/20 15:38:22 by hdupire          ###   ########.fr       */
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

int	env_infernal(t_env *env, ...)
{
	t_env	*ptr;
	char	*prepend;
	va_list	list;
	int		i;

	ptr = env;
	va_start(list, env);
	prepend = va_arg(list, char *);
	while (ptr)
	{
		if (ptr->is_exported)
		{
			if (prepend != NULL)
				printf("%s", prepend);
			printf("%s=", ptr->key);
			if (prepend)
				printf("\"");
			if (ptr->value != NULL)
				{
				i = 0;
				while (ptr->value[i])
				{
					printf("%s", ptr->value[i]);
					if (ptr->value[++i])
						printf(":");
				}
			}
			if (prepend)
				printf("\"");
			printf("\n");
		}
		ptr = ptr->next;
	}
	return (0);
}
