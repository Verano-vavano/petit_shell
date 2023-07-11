/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_et_damnation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:36:51 by tcharanc          #+#    #+#             */
/*   Updated: 2023/07/11 15:54:26 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include <stdlib.h>

void	unset_et_damnation(t_command *lexed, t_env *env)
{
	lexed = lexed->next;
	while (lexed)
	{
		del_env(&env, lexed->content);
		lexed = lexed->next;
	}
}
