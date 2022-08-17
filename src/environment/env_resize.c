/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:45:48 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/15 16:18:10 by hoomen           ###   ########.fr       */
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
		ft_memset(new_hash + i, 0, sizeof(t_env_hash));
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

int	shrink_env(t_env *env)
{
	int		src;
	int		dst;
	int		del;

	src = 0;
	while (src < env->size && env->envp[src] != NULL)
		src++;
	dst = src;
	del = 0;
	while (src < env->size)
	{
		if (env->envp[src] == NULL)
			src++;
		else
		{
			env->envp[dst] = env->envp[src];
			env->env_hash[dst].key = env->env_hash[src].key;
			env->env_hash[dst].value = env->env_hash[src].value;
			env->env_hash[dst].for_export = env->env_hash[src].for_export;
			del++;
		}
	}
	env->size -= del;
	env->free += del;
	return (0);
}

					
