/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_et_damnation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:36:51 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/05 15:51:48 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"
#include <stdlib.h>

int	unset_et_damnation(char **cmd, t_env **env)
{
	cmd++;
	while (*cmd)
	{
		env_del(*cmd, env);
		cmd++;
	}
	return (0);
}
