/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tilde.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:09:45 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/12 16:52:13 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	*get_from_pwd(char *pwd)
{
	if (!ft_strncmp(pwd, "/Users/", 7) && ft_strlen(pwd) > 7)
		return (ft_strndup(pwd, 7 + ft_strchr_int(pwd + 7, '/')));
	return (0);
}

char	*rescue_tilde_funk(t_env *env, char *pwd)
{
	char	*home;

	(void) env;
	if (pwd)
	{
		home = get_from_pwd(pwd);
		printf("YAY = %s\n", home);
		if (home)
			return (home);
	}
	return (0);
}
