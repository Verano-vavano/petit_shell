/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:28:04 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/31 22:28:18 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

char	*get_output(int *pipes)
{
	char	buffer[1024];
	char	*ret;
	char	*temp;
	int		readed;

	ret = ft_calloc(1, sizeof (char));
	if (!ret)
		return (0);
	readed = 1023;
	close(pipes[1]);
	while (readed == 1023)
	{
		readed = read(pipes[0], buffer, 1023);
		if (readed == 0 || readed == -1)
			break ;
		buffer[readed] = 0;
		temp = ft_strjoin(ret, buffer);
		free(ret);
		if (!temp)
			return (0);
		ret = temp;
	}
	ret[ft_strlen(ret) - 1] = 0;
	return (ret);
}
