/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hellias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:48:20 by hdupire           #+#    #+#             */
/*   Updated: 2023/09/29 20:24:20 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

static void	print_alias_key(t_alias *alias)
{
	printf("alias %s='%s'\n", alias->cmd, alias->replacer);
}

static void	swap_alias(t_alias *p, t_alias *a, t_alias *n, t_tool *t)
{
	if (t->alias_start == a)
		t->alias_start = n;
	if (t->alias_end == n)
		t->alias_end = a;
	if (p)
		p->next = n;
	a->next = n->next;
	n->next = a;
}

static bool	sort_spin(t_tool *tool)
{
	bool	changed;
	int		diff;
	t_alias	*alias;
	t_alias	*prev;

	prev = 0;
	changed = false;
	alias = tool->alias_start;
	while (alias && alias->next)
	{
		diff = ft_strcmp(alias->cmd, alias->next->cmd);
		if (diff > 0)
		{
			swap_alias(prev, alias, alias->next, tool);
			changed = true;
		}
		prev = alias;
		alias = alias->next;
	}
	return (changed);
}

static void	sort_alias(t_tool *tool)
{
	if (!tool->alias_start)
		return ;
	while (sort_spin(tool))
		continue ;
}

static void	print_whole_alias(t_tool *tool)
{
	t_alias	*alias;

	sort_alias(tool);
	alias = tool->alias_start;
	while (alias)
	{
		print_alias_key(alias);
		alias = alias->next;
	}
}

static bool	print_alias(char *arg, t_tool *tool)
{
	t_alias	*alias;

	alias = tool->alias_start;
	while (alias)
	{
		if (!ft_strcmp(alias->cmd, arg))
		{
			print_alias_key(alias);
			return (true);
		}
		alias = alias->next;
	}
	return (false);
}

static bool	change_alias_val(char *key, char *alias, t_tool *tool)
{
	t_alias	*alias_search;

	alias_search = tool->alias_start;
	while (alias_search)
	{
		if (!ft_strcmp(key, alias_search->cmd))
		{
			free(key);
			free(alias_search->replacer);
			alias_search->replacer = alias;
			return (true);
		}
		alias_search = alias_search->next;
	}
	return (false);
}

static bool	add_key_alias(char *key, char *alias, t_tool *tool)
{
	t_alias	*new_alias;

	if (change_alias_val(key, alias, tool))
		return (0);
	new_alias = ft_calloc(1, sizeof (t_alias));
	if (!new_alias)
		return (1);
	new_alias->cmd = key;
	new_alias->replacer = alias;
	if (tool->alias_end)
		tool->alias_end->next = new_alias;
	else
		tool->alias_start = new_alias;
	tool->alias_end = new_alias;
	return (0);
}

static bool	add_alias(char *arg, t_tool *tool)
{
	char	*key;
	char	*alias;
	int		equal_sign;
	bool	ret;

	equal_sign = ft_strchr_int(arg, '=');
	if (!arg[equal_sign])
		return (false);
	key = ft_strndup(arg, equal_sign);
	if (!key)
		return (false);
	if (ft_strchr(key, ' '))
	{
		printfd(ERR, "alias: `%s': invalid alias name\n", key);
		free(key);
		return (false);
	}
	alias = ft_strdup(arg + equal_sign + 1);
	if (!alias)
	{
		free(key);
		return (false);
	}
	ret = add_key_alias(key, alias, tool);
	if (!ret)
		return (true);
	free(key);
	free(alias);
	return (false);
}

int	hellias(char **args, t_tool *tool)
{
	char	*ptr;

	if (!tool)
		return (1);
	args++;
	if (!args[0])
		print_whole_alias(tool);
	else
	{
		while (*args)
		{
			ptr = ft_strchr(*args, '=');
			if (ptr && ptr != *args)
			{
				if (!add_alias(*args, tool) && !args[1])
					return (1);
			}
			else if (!print_alias(*args, tool))
			{
				printfd(ERR, "alias: %s: not found\n", *args);
				if (!args[1])
					return (1);
			}
			args++;
		}
	}
	return (0);
}
