/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:33:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/11 14:22:43 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* updates the hash table "arr_pairs" (part of the env struct).
 * Searches for matching key, makes new value using ft_strdup
 * Replaces old value by new value, freeing old value.
 * Returns 0 upon succes.
 * Returns error code and sets exit_status if a problem occurs (malloc fails
 * or the environment variable was not set (i.e. no matching key is found)
 */
int	update_arr_pairs(t_env *env, char *key, char *new_value)
{
	int		i;
	char	*new_value_dup;

	i = 0;
	while (i < env->size)
	{
		if (ft_strcmp(env->arr_pairs[i].key, key) == 0)
		{
			new_value_dup = ft_strdup(new_value);
			if (new_value_dup == NULL)
			{
				ms_exit_status = ENOMEM;
				return (NO_MEM);
			}
			free(env->arr_pairs[i].value);
			env->arr_pairs[i].value = new_value_dup;
			break ;
		}
		i++;
	}
	if (i == env->size)
	{
		ms_exit_status = 1;
		return (NO_ENV);
	}
	return (0);
}

/* Makes a string 'comp' by joining key and "=" together, calling ft_strjoin
 * Sets comp_len to the length of comp
 * Cycles through envp and, at each entry, compares comp_len bytes of the given entry with comp.
 * If both are equal, proceeds to make the new entry (joining comp and the new value together) and
 * replaces the old entry with the new entry (freeing the  old entry).
 * on succes, returns 0.
 * If no matching entry is found, returns NO_ENV and sets exit status to 1.
 * If malloc fails, returns NO_MEM and sets exit status to ENOMEM
 */
int	update_envp(t_env *env, char *key, char *new_value)
{
	char	*comp;
	char	*new_entry;
	int		comp_len;
	int		i;

	comp = ft_strjoin(key, "=");
	if (comp == NULL)
	{
		ms_exit_status = ENOMEM;
		return (NO_MEM);
	}
	comp_len = ft_strlen(comp);
	i = 0;
	while (env->envp[i] != NULL)
	{
		if (ft_strncmp(env->envp[i], comp, comp_len) == 0)
		{
			new_entry = ft_strjoin(comp, new_value);
			if (new_entry == NULL)
			{
				ms_exit_status = ENOMEM;
				free(comp);
				return (NO_MEM);
			}
			free(env->envp[i]);
			env->envp[i] = new_entry;
		}
		i++;
	}
	free(comp);
	if (env->envp[i] == NULL)
	{
		ms_exit_status = 1;
		return (NO_ENV);
	}
	return (0);
}

/* takes as parameter the env struct, the key to be updated and the new value.
 * Calls update_arr_pairs to update the hash table (array of key-value pairs, env->arr_pairs)
 * Calls update_envp to update envp (stored in env->envp)
 * If one of them could not be updated correctly, returns an error code. Otherwwise, returns 0 */
int	update_env(t_env *env, char *key, char *new_value)
{
	int	ret;

	ret = update_arr_pairs(env, key, new_value);
	if (ret)
		return (ret);
	ret = update_envp(env, key, new_value);
	return (ret);
}

