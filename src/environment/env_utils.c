/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 11:59:14 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/14 18:03:05 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* clears the env struct. Looks always one element past env->size in case a
 * resizing or update was left incomplete.
 */
void	clear_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->size + 1)
	{
		free(env->env_hash[i].key);
		free(env->env_hash[i].value);
		free(env->envp[i]);
		i++;
	}
	free(env->env_hash);
	free(env->envp);
	free(env->cwd);
}

/* returns the index of a key in the env hash table. In case no key is found,
 * -1 is returned
 */
int	key_index(t_env *env, char *key)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (ft_strcmp(env->env_hash[i].key, key) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/* returns a pointer to the value for a given key. Returns NULL if the key is
 * not found or if the value is not set
 */
char	*find_value(t_env *env, char *key)
{
	int	i;

	i = key_index(env, key);
	if (i == -1)
		return (NULL);
	return (env->env_hash[i].value);
}

