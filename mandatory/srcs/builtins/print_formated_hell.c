/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_hell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:25:06 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/05 15:32:01 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	pff_readfile(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && *line)
	{
		echo_des_enfers((char *[]) {"echo", "-ne", line, 0});
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

// Builtin qui lit un fichier ligne par ligne et output avec 'echo -e'
int	print_formated_hell(char **cmd)
{
	int	ret;
	int	fd;

	ret = 0;
	cmd++;
	while (*cmd)
	{
		fd = open(*cmd, O_RDONLY);
		if (fd == -1)
		{
			printfd(ERR, "pff: %s: cannot open file\n", *cmd);
			ret = 1;
		}
		else
			pff_readfile(fd);
		cmd++;
	}
	return (ret);
}
