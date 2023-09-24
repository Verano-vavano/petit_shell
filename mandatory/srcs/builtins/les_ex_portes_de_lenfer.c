/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_ex_portes_de_lenfer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:45:59 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/22 12:32:30 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shellpticflesh.h"
#include <string.h>

char	**dup_paths(char **paths)
{
	int		i;
	char	**cpy;

	i = 0;
	while (paths[i])
		i++;
	cpy = malloc(sizeof(char *) * i + 1);
	if (!cpy)
		return (0);
	i = -1;
	while (paths[++i])
		cpy[i] = ft_strdup(paths[i]);
	cpy[i] = NULL;
	return (cpy);
}

static bool	check_assign(char *s)
{
	int	i;

	if (is_valid_var_char(s[0]) && is_num(s[0]))
		return (false);
	else if (s[0] == '=')
		return (false);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (!is_valid_var_char(s[i]))
			return (s[i] == '+' && s[i + 1] == '=');
		i++;
	}
	return (true);
}

static int	print_env(t_env *ptr)
{
	t_env	*sorted_env;

	sorted_env = NULL;
	while (ptr)
	{
		env_add(dup_env(ptr), &sorted_env);
		ptr = ptr->next;
	}
	sort_env(sorted_env);
	ptr = sorted_env;
	env_infernal(sorted_env, true);
	free_whole_env(sorted_env);
	return (0);
}

int	les_ex_portes_de_lenfer(char **cmd, t_env **env)
{
	t_env	*ptr;
	int		ret;

	if (!cmd[1] && (!env || !(*env)))
		return (0);
	if (env && *env)
		ptr = *env;
	if (!cmd[1])
		return (print_env(ptr));
	cmd++;
	ret = 0;
	while (*cmd)
	{
		if (check_assign(*cmd))
		{
			if (!env || !(*env))
				*env = env_new(*cmd, true);
			else
				env_update(*cmd, true, env);
		}
		else
		{
			printfd(ERR, "export : `%s': not a valid identifier\n", *cmd);
			if (!cmd[1])
				return (1);
		}
		cmd++;
	}
	return (ret);
}
