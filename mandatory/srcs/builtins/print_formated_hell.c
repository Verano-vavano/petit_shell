/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formated_hell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:25:06 by hdupire           #+#    #+#             */
/*   Updated: 2023/10/07 12:02:25 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static char	**set_args_echo(char *line)
{
	char	**cmd;

	cmd = ft_calloc(4, sizeof (char *));
	if (!cmd)
		return (0);
	cmd[0] = ft_strdup("echo");
	if (cmd[0])
		cmd[1] = ft_strdup("-ne");
	if (cmd[0] && cmd[1])
		cmd[2] = line;
	else
	{
		free_char_etoile_etoile(cmd);
		return (0);
	}
	return (cmd);
}

static void	pff_readfile(int fd)
{
	char	*line;
	char	**cmd;

	line = get_next_line(fd);
	while (line && *line)
	{
		cmd = set_args_echo(line);
		if (cmd)
		{
			echo_des_enfers(cmd);
			free_char_etoile_etoile(cmd);
		}
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
