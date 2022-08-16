/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:10:53 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 09:44:57 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* These functions add a new variable to the environment struct, either
 * with one string as a parameter (full envp entry of type "key" or "key=value")
 * or two strings (key and value). If a full envp entry is passed, it is
 * duplicated and added to the envp array, and, additionally, key and value
 * strings are produced and added to the hash table of the env struct. 
 * If a key and a value are passed, both duplicated and added to the hash table 
 * and an a additional full envp entry ("key" or "key=value") is produced and added
 * to the envp array.
 * Functions return 0 on succes, -1 in case a system error occurs.
 */

/* changes equal sign to nul byte so that envp_entry becomes a
 * pointer to the key only. Sets value_ptr (passed by reference) to the byte after
 * the equal sign or to nul if no equal sign is found.
 * returns -1 if an equal sign was found, otherwise, returns the index of the 
 * equalsign
 */
int	manipulate_ptrs(char *envp_entry, char **value_ptr)
{
	char	*ptr;

	ptr = envp_entry;
	while (*ptr && *ptr != '=')
		ptr++;
	if (*ptr == '=')
	{
		*ptr = '\0';
		*value_ptr = ptr + 1;
		return (ptr - envp_entry);
	}
	*value_ptr = NULL;
	return (-1);
}

/* converts two strings (key and value) to a full envp entry of 
 * type "key=value" or "key".
 */ 
static int	key_value_to_envp_entry(char **envp_entry, char *key, char *value)
{
	char *with_equalsign;

	if (value == NULL)
	{
		*envp_entry = ft_strdup(key);
		if (*envp_entry == NULL)
			return (-1);
		return (0);
	}
	with_equalsign = ft_strjoin(key, "=");
	if (with_equalsign == NULL)
		return (-1);
	*envp_entry = ft_strjoin(with_equalsign, value);
	free(with_equalsign);
	if (*envp_entry == NULL)
		return (-1);
	return (0);
}

/* change value to existing key
 * if key does not exist, add new key_value pair and set for_export to EXPORT
 * return -1 for error
 * return 0 if new key was created
 * return 1 if value was succesfully added or changed
 */
int	change_value(t_env *env, char *value, char *key, int i)
{
	char	*new_value;
	char	*new_envp_entry;

	if (i == UNKNOWN)
		i = key_index(env, key);
	if (i == -1) 
		return (add_key_value_pair_to_env(env, key, value, EXPORT));
	new_value = ft_strdup(value);
	if (new_value == NULL)
		return (-1);
	if (key_value_to_envp_entry(&new_envp_entry, key, value) == -1)
		return (-1);
	free(env->env_hash[i].value);
	env->env_hash[i].value = new_value;
	free(env->envp[i]);
	env->envp[i] = new_envp_entry;
	return (1);
}

/* adds a full declaration string (of type "key" or "key=value") to the env 
 * struct
 */
int	add_envp_entry_to_env(t_env *env, char *envp_entry, bool for_export)
{
	char	*key;
	char	*value_ptr;
	char	*value;
	int		i;

	if (env->free == 0 && resize_env(env) == -1)
		return (-1);
	i = env->size;	
	env->envp[i] = ft_strdup(envp_entry);
	if (env->envp[i] == NULL)
		return (-1);
	manipulate_ptrs(envp_entry, &value_ptr);
	key = ft_strdup(envp_entry);
	if (key == NULL)
		return (-1);
	value = ft_strdup(value_ptr);
	if (value == NULL && value_ptr != NULL)
		return (-1);
	env->env_hash[i].key = key;
	env->env_hash[i].value = value;
	env->env_hash[i].for_export = for_export;
	env->size++;
	env->free--;
	return (sort_hash_entry(env, i));
}


/* adds a key and a value to env struct. 
 */
int	add_key_value_pair_to_env(t_env *env, char *key, char *value, bool for_export)
{
	char	*envp_entry;
	char	*key_dup;
	char	*value_dup;
	int		i;

	if (env->free == 0 && resize_env(env) == -1)
		return (-1);
	if (key_value_to_envp_entry(&envp_entry, key, value) == -1)
		return (-1);
	i = env->size;
	env->envp[i] = envp_entry;
	key_dup = ft_strdup(key);
	if (key_dup == NULL)
		return (-1);
	env->env_hash[i].key = key_dup;
	value_dup = ft_strdup(value);
	if (value != NULL && value_dup == NULL)
		return (-1);
	env->env_hash[i].value = value_dup;
	env->env_hash[i].for_export = for_export;
	env->size++;
	env->free--;
	return (sort_hash_entry(env, i));
}

