/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal-injection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:26:10 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/05 11:49:29 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static int	rand_num(void)
{
	int		tmp_file;
	int		rand;
	int		pid;
	char	c;

	pid = fork();
	if (pid == 0)
	{
		tmp_file = open("/tmp/s-hell", O_CREAT | O_WRONLY | O_TRUNC, 0777);
		dup2(tmp_file, STDOUT_FILENO);
		close(tmp_file);
		execve("/usr/bin/jot", (char *[]){"jot", "-r", "1", "0", "9", 0}, 0);
		return (0);
	}
	else
	{
		waitpid(pid, 0, 0);
		tmp_file = open("/tmp/s-hell", O_RDONLY);
		read(tmp_file, &c, sizeof(c));
		rand = (c - '0') + 1;
		close(tmp_file);
		unlink("/tmp/s-hell");
		return (rand);
	}
}

void	metal_injection(void)
{
	int		group_num;
	int		i;
	int		fd;
	char	*group;

	i = 0;
	group_num = rand_num();
	fd = open("/Users/tcharanc/code/minishell/mandatory/shell_on_earth.txt", O_RDONLY);
	while (i < group_num)
	{
		group = get_next_line(fd);
		i++;
	}
	printf("%s", group);
}
