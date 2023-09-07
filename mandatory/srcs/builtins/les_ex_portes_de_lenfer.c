/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_ex_portes_de_lenfer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:45:59 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/07 10:23:28 by hdupire          ###   ########.fr       */
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
	i = -1;
	while (paths[++i])
		cpy[i] = ft_strdup(paths[i]);
	cpy[i] = NULL;
	return (cpy);
}

t_env	*dup_env(t_env *env)
{
	t_env	*new;
	int		arr_size;
	int		i;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(env->key);
	if (ft_strcmp(new->key, "CDPATH") == 0)
		printf("salut mdr\n");
	if (env->value != NULL)
	{
		arr_size = get_char_array_size(env->value);
		new->value = malloc(sizeof(char *) * (arr_size + 1));
		i = -1;
		while (env->value[++i])
			new->value[i] = ft_strdup(env->value[i]);
		new->value[i] = NULL;
	}
	else
		new->value = NULL;
	new->next = NULL;
	new->is_exported = env->is_exported;
	return (new);
}

void	swap_content(t_env *curr, t_env *next)
{
	char	*yo_key;
	char	**yo_value;

	yo_key = curr->key;
	yo_value = curr->value;
	curr->key = next->key;
	curr->value = next->value;
	next->key = yo_key;
	next->value = yo_value;
}

void	sort_env(t_env *head)
{
	int		swapped;
	t_env	*ptr;

	swapped = 1;
	while (swapped == 1)
	{
		swapped = 0;
		ptr = head;
		while (ptr->next)
		{
			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
			{
				swap_content(ptr, ptr->next);
				swapped = 1;
			}
			ptr = ptr->next;
		}
	}
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

int	les_ex_portes_de_lenfer(char **cmd, t_env **env)
{
	t_env	*ptr;
	t_env	*sorted_env;
	int		ret;

	if (!cmd[1] && (!env || !(*env)))
		return (0);
	if (env && *env)
		ptr = *env;
	if (!cmd[1])
	{
		sorted_env = NULL;
		while (ptr)
		{
			env_add(dup_env(ptr), &sorted_env);
			ptr = ptr->next;
		}
		sort_env(sorted_env);
		ptr = sorted_env;
		env_infernal(sorted_env, "declare -x ", NULL);
		free_whole_env(sorted_env);
		return (0);
	}
	cmd++;
	ret = 0;
	while (*cmd)
	{
		if (check_assign(*cmd))
		{
			if (!env || !(*env))
				*env = env_new(*cmd, true);
			else
				env_update(*cmd, true, *env, NULL);
		}
		else
		{
			write(2, "export : `", 10);
			write(2, *cmd, ft_strlen(*cmd));
			write(2, "': not a valid identifier\n", 26);
			ret = 1;
		}
		cmd++;
	}
	return (ret);
}
