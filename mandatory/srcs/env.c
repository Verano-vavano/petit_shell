/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharanc <code@nigh.one>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:07:11 by tcharanc          #+#    #+#             */
/*   Updated: 2023/09/16 13:52:20 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellpticflesh.h"

char	**one_split(char *str, char c)
{
	char	**ret;
	int		index_c;

	index_c = ft_strchr_int(str, c);
	ret = ft_calloc(2 + (str[index_c]), sizeof (char *));
	if (!ret)
		return (0);
	ret[0] = ft_strndup(str, index_c);
	if (!ret[0])
	{
		free(ret);
		return (0);
	}
	if (str[index_c])
		ret[1] = ft_strdup(str + index_c + 1);
	return (ret);
}

t_env	*env_new(char *env_var, bool is_exported)
{
	t_env	*new;
	char	**tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	tmp = one_split(env_var, '=');
	if (!tmp)
		return (free(new), NULL);
	new->key = ft_strdup(tmp[0]);
	if (!new->key)
	{
		free_char_etoile_etoile(tmp);
		return (free(new), NULL);
	}
	if (new->key[ft_strlen(new->key) - 1] == '+')
		new->key[ft_strlen(new->key) - 1] = '\0';
	new->value = NULL;
	if (tmp[1])
		new->value = ft_strdup(tmp[1]);
	new->next = NULL;
	new->is_exported = is_exported;
	free_char_etoile_etoile(tmp);
	return (new);
}

static void	init_variables(t_env **env)
{
	char	cwd[1024];
	char	*temp_pwd;

	if (!env_contain("PATH", *env))
		env_add(env_new(STD_PATH, true), env);
	if (!env_contain("PS1", *env))
		env_add(env_new(STD_PS1, false), env);
	if (!env_contain("PS2", *env))
		env_add(env_new(STD_PS2, false), env);
	if (!env_contain("PWD", *env) && getcwd(cwd, 1024))
	{
		temp_pwd = ft_strjoin("PWD=", cwd);
		if (temp_pwd)
		{
			env_add(env_new(temp_pwd, false), env);
			free(temp_pwd);
		}
	}
	increment_shlvl(env);
}

t_env	*env_init(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
		env_add(env_new(envp[i++], true), &env);
	init_variables(&env);
	return (env);
}
