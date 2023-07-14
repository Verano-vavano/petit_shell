/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_et_damnation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:36:51 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/14 17:53:02 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include <stdlib.h>

void	unset_et_damnation(t_command *lexed, t_env *env)
{
	lexed = lexed->next;
	while (lexed)
	{
		env_del(lexed->content, &env);
		lexed = lexed->next;
	}
}
