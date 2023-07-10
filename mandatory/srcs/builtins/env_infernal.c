/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_infernal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:47:35 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/10 18:30:34 by tcharanc         ###   ########.fr       */
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

void	env_infernal(t_env *env, ...)
{
	t_env	*ptr;
	char	*prepend;
	va_list	list;

	ptr = env;
	va_start(list, env);
	prepend = va_arg(list, char *);
	while (ptr)
	{
		if (prepend != NULL)
			printf("%s", prepend);
		printf("%s=", ptr->key);
		if (ptr->value != NULL)
		{
			if (ft_strcmp("PATH", ptr->key) == 0)
				print_paths(ptr);
			else
				printf("%s", ptr->value[0]);
		}
		printf("\n");
		ptr = ptr->next;
	}
}
