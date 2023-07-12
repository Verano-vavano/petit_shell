/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:05:16 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/12 17:29:56 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"

int	update_env(char *key, char **value, t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while(ptr)
		if (ft_strcmp(key, ptr->key) == 0)
		{
			free_char_etoile_etoile(ptr->value);
			ptr->value = value;
			return (1);
		}
		else
			ptr = ptr->next;
	return (0);
}
