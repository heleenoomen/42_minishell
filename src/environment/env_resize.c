/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:45:48 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/14 13:54:16 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	resize_hashtable(t_env *env)
{
	t_env_hash	*new_hash;
	int			i;

	new_hash = malloc((env->size + 256) * sizeof(t_env_hash));
	if (new_hash == NULL)
		return (-1);
	i = 0;
	while (i < env->size)
	{
		new_hash[i].key = env->env_hash[i].key;
		new_hash[i].value = env->env_hash[i].value;
		new_hash[i].for_export = env->env_hash[i].for_export;
		i++;
	}
	env->free = 256;
	while (i < env->free + 1)
	{
		ft_memset(new_hash + i, 0, sizeof(t_env_hash);
		i++;
	}
	free(env->env_hash);
	env->env_hash = new_hash;
	return (0);
}

static int resize_envp(t_env *env)
{
	char	**new_envp;
	int		i;

	new_envp = malloc((env->size + 256) * sizeof(char *));
	if (new_envp == NULL)
		return (-1);
	i = 0;
	while (i < env->size)
	{
		new_envp[i] = env->envp[i];
		i++;
	}
	while (i < env->free)
	{
		new_envp[i] = NULL;
		i++;
	}
	free(env->envp);
	env->envp = new_envp;
	return (0);
}

int	resize_env(t_env *env)
{
	if (env->size >= INT_MAX - 256)
		return (-1);
	if (resize_hashtable(env) == -1)
		return (-1);
	if (resize_envp(env) == -1)
		return (-1);
	return (0);
}

