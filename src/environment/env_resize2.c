/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_resize2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:45:48 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 16:51:10 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* copies data from old hash entry into new hash entry
 */
void	copy_hash(t_env_hash *new_hash, t_env_hash old_hash)
{
	new_hash->key = old_hash.key;
	new_hash->value = old_hash.key;
	new_hash->for_export = old_hash.for_export;
}

/* grows hash table if needed. if more than 63 entries are currently 
 * deleted, clean_env_hash is called instead */
int	grow_env_hash(t_env *env)
{
	t_env_hash	*new_hash;
	int			i;

	if (env->deleted > 63)
		return (cleanup_env_hash(env));
	if (env->size >= INT_MAX - 256)
		return (-1);
	new_hash = malloc((env->size + 256) * sizeof(t_env_hash));
	if (new_hash == NULL)
		return (-1);
	i = 0;
	env->free += 256;
	while (i < env->size + env->deleted)
	{
		copy_hash(new_hash + i, env->env_hash[i]);
		i++;
	}
	while (i < env->free + 1)
	{
		ft_memset(new_hash + i, 0, sizeof(t_env_hash));
		i++;
	}
	free(env->env_hash);
	env->env_hash = new_hash;
	return (0);
}

/* shrinks hash table if there is 256 free bytes or more
 */
void	shrink_env_hash(t_env *env)
{
	int			free_up;
	int			total;
	t_env_hash	*new;
	int			i;

	total = env->free + 1 + env->size + env->deleted;
	free_up = (env->free % 256) * 256;
	new = malloc((total - free_up) * sizeof(t_env_hash));
	if (new == NULL)
		return ;
	i = 0;
	while (i < env->size)
	{
		copy_hash(new + i, env->env_hash[i]);
		i++;
	}
	while (i < env->free + 1)
	{
		ft_memset(new + i, 0, sizeof(t_env_hash));
		i++;
	}
	free(env->env_hash);
	env->env_hash = new;
}

/* moves hash table entries if too much space is being wasted */
int	cleanup_env_hash(t_env *env)
{
	int		src;
	int		dst;

	src = 0;
	dst = src;
	while (src < env->size + env->deleted)
	{
		if (env->env_hash[src].key != NULL)
		{
			if (dst != src)
			{
				copy_hash(&(env->env_hash[dst]), env->env_hash[src]);
				ft_memset(&(env->env_hash[src]), 0, sizeof(t_env_hash));
			}
			dst++;
		}
		src++;
	}
	env->free += env->deleted;
	env->deleted = 0;
	if (env->free > 255)
		shrink_env_hash(env);
	return (0);
}

