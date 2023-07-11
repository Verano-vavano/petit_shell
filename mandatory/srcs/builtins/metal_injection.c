/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal-injection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:26:10 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/11 20:12:08 by tcharanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"
#include "limits.h"
#include <limits.h>

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

	group_num = rand_num();
	if (group_num == 0)
		printf("Shelldren of Bodom\n");
	else if (group_num == 1)
		printf("Shellpultura\n");
	else if (group_num == 2)
		printf("Shelltic Frost\n");
	else if (group_num == 3)
		printf("Shlayer\n");
	else if (group_num == 4)
		printf("Shellpknot\n");
	else if (group_num == 5)
		printf("Shellhammer\n");
	else if (group_num == 6)
		printf("Alice in Shells\n");
	else if (group_num == 7)
		printf("Dimmu Shellgir\n");
	else if (group_num == 8)
		printf("Megashellth\n");
	else
		printf("Shellcidal Tendencies\n");
}
// nine inch shell
// ready set fall
// shell against the machine
// Shell Theater
// Rapshelldy of Fire
// Goshellra
// shelltiricon
// Shellptic Flesh
// all shell perish
// Shelltones
// Shellstafir
// Shell et Ardor
// Black Shellbath
// Shelloween
// Shellgod Apocalypse
// Shellpanther
// MoonShpell
// Hangman's shell
// Five Finger shell Punch
// Meshulluga
