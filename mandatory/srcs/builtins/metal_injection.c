/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal-injection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:26:10 by hdupire           #+#    #+#             */
/*   Updated: 2023/08/10 15:19:29 by hdupire          ###   ########.fr       */
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
		printf("Shell Panther\n");
	else if (group_num == 32)
		printf("In Shell\n");
	else if (group_num == 33)
		printf("Black Shellbath\n");
}

void	rescue_easter_funk2(int group_num)
{
	if (group_num == 20)
		printf("Napalm Shell\n");
	else if (group_num == 21)
		printf("Shelloween\n");
	else if (group_num == 22)
		printf("Shell et Ardor\n");
	else if (group_num == 23)
		printf("Shellgod Apocalypse\n");
	else if (group_num == 24)
		printf("Shellpanther\n");
	else if (group_num == 25)
		printf("MoonShpell\n");
	else if (group_num == 26)
		printf("Hangman's shell\n");
	else if (group_num == 27)
		printf("Five Finger shell Punch\n");
	else if (group_num == 28)
		printf("Meshulluga\n");
	else if (group_num == 29)
		printf("Shellstafir\n");
	else if (group_num == 30)
		printf("MotorShell\n");
	else
		rescue_easter_funk3(group_num);
}

void	rescue_easter_funk1(int group_num)
{
	if (group_num == 9)
		printf("Shellcidal Tendencies\n");
	else if (group_num == 10)
		printf("nine inch shell\n");
	else if (group_num == 11)
		printf("ready set fall\n");
	else if (group_num == 12)
		printf("shell against the machine\n");
	else if (group_num == 13)
		printf("Shell Theater\n");
	else if (group_num == 14)
		printf("Rapshelldy of Fire\n");
	else if (group_num == 15)
		printf("Goshellra\n");
	else if (group_num == 16)
		printf("shelltiricon\n");
	else if (group_num == 17)
		printf("Shellptic Flesh\n");
	else if (group_num == 18)
		printf("all shell perish\n");
	else if (group_num == 19)
		printf("Shelltones\n");
	else
		rescue_easter_funk2(group_num);
}

int	metal_injection(void)
{
	int		group_num;

	group_num = ft_randint(0, 34);
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
		rescue_easter_funk1(group_num);
	return (0);
}
