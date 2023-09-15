/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal-injection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:26:10 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/15 18:07:56 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"
#include "limits.h"
#include <limits.h>
#include <stdio.h>

void	rescue_easter_funk3(int group_num)
{
	if (group_num == 31)
		printfd(STDOUT_FILENO, "Shell Panther\n");
	else if (group_num == 32)
		printfd(STDOUT_FILENO, "In Shell\n");
	else if (group_num == 33)
		printfd(STDOUT_FILENO, "Black Shellbath\n");
}

void	rescue_easter_funk2(int group_num)
{
	if (group_num == 20)
		printfd(STDOUT_FILENO, "Napalm Shell\n");
	else if (group_num == 21)
		printfd(STDOUT_FILENO, "Shelloween\n");
	else if (group_num == 22)
		printfd(STDOUT_FILENO, "Shell et Ardor\n");
	else if (group_num == 23)
		printfd(STDOUT_FILENO, "Shellgod Apocalypse\n");
	else if (group_num == 24)
		printfd(STDOUT_FILENO, "Shellpanther\n");
	else if (group_num == 25)
		printfd(STDOUT_FILENO, "MoonShpell\n");
	else if (group_num == 26)
		printfd(STDOUT_FILENO, "Hangman's shell\n");
	else if (group_num == 27)
		printfd(STDOUT_FILENO, "Five Finger shell Punch\n");
	else if (group_num == 28)
		printfd(STDOUT_FILENO, "Meshulluga\n");
	else if (group_num == 29)
		printfd(STDOUT_FILENO, "Shellstafir\n");
	else if (group_num == 30)
		printfd(STDOUT_FILENO, "MotorShell\n");
	else
		rescue_easter_funk3(group_num);
}

void	rescue_easter_funk1(int group_num)
{
	if (group_num == 9)
		printfd(STDOUT_FILENO, "Shellcidal Tendencies\n");
	else if (group_num == 10)
		printfd(STDOUT_FILENO, "nine inch shell\n");
	else if (group_num == 11)
		printfd(STDOUT_FILENO, "ready set fall\n");
	else if (group_num == 12)
		printfd(STDOUT_FILENO, "shell against the machine\n");
	else if (group_num == 13)
		printfd(STDOUT_FILENO, "Shell Theater\n");
	else if (group_num == 14)
		printfd(STDOUT_FILENO, "Rapshelldy of Fire\n");
	else if (group_num == 15)
		printfd(STDOUT_FILENO, "Goshellra\n");
	else if (group_num == 16)
		printfd(STDOUT_FILENO, "shelltiricon\n");
	else if (group_num == 17)
		printfd(STDOUT_FILENO, "Shellptic Flesh\n");
	else if (group_num == 18)
		printfd(STDOUT_FILENO, "all shell perish\n");
	else if (group_num == 19)
		printfd(STDOUT_FILENO, "Shelltones\n");
	else
		rescue_easter_funk2(group_num);
}

int	metal_injection(void)
{
	int		group_num;

	group_num = ft_randint(0, 34);
	if (group_num == 0)
		printfd(STDOUT_FILENO, "Shelldren of Bodom\n");
	else if (group_num == 1)
		printfd(STDOUT_FILENO, "Shellpultura\n");
	else if (group_num == 2)
		printfd(STDOUT_FILENO, "Shelltic Frost\n");
	else if (group_num == 3)
		printfd(STDOUT_FILENO, "Shlayer\n");
	else if (group_num == 4)
		printfd(STDOUT_FILENO, "Shellpknot\n");
	else if (group_num == 5)
		printfd(STDOUT_FILENO, "Shellhammer\n");
	else if (group_num == 6)
		printfd(STDOUT_FILENO, "Alice in Shells\n");
	else if (group_num == 7)
		printfd(STDOUT_FILENO, "Dimmu Shellgir\n");
	else if (group_num == 8)
		printfd(STDOUT_FILENO, "Megashellth\n");
	else
		rescue_easter_funk1(group_num);
	return (0);
}
