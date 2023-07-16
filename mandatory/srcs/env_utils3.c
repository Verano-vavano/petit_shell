/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupire <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:40:28 by hdupire           #+#    #+#             */
/*   Updated: 2023/07/16 15:58:38 by hdupire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	env_size(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		if (env->is_local)
			n++;
		env = env->next;
	}
	return (n);
}

char	**re_char_etoile_etoilise_env(t_env *env)
{
	char	**c_env;
	int		len;
	int		i;

	len = env_size(env);
	c_env = ft_calloc(len + 1, sizeof (char *));
	if (c_env == 0)
		return (0);
	i = 0;
	while (env)
	{
		if (env->is_local)
		{
			c_env[i] = get_env_val(env);
			if (c_env[i] == 0)
			{
				free_char_etoile_etoile(c_env);
				return (0);
			}
			i++;
		}
	}
}
