/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:10:53 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 19:58:09 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* appends a new key value pair to the env->env_hash array
 */
int	add_to_hash(t_env *env, char *key, char *value, for_export)
{
	if (env->free == NULL || resize_env(env) == -1)
	{
		clear_node(env->tree, key);
		return (-1);
	}
	env->env_hash[size].key = key;
	env->env_hash[size].value = value;
	env->for_export = for_export;
}

/* adds a key and a value to the tree, then to the hash table
 */
int	add_key_value_to_env(t_env *env, char *key, char *value, bool for_export)
{
	t_env_tree **branch;
	t_env_tree	**leaf;
	t_env_tree	*new;
	
	branch = &(env->tree);
	leaf = descend_tree_ins(branch, key);
	if (*leaf != NULL)
	{
		update_value(leaf, value, for_export);
		update_hash(env, *leaf);
		return (0);
	}
	new = new_tree_node(key, value, for_export);
	if (new == NULL)
		return (free_return((void) key, (void) value, -1);
	*leaf = new;
	return (add_to_hash(env, key, value, for_export));
}

/* converts a string of type "key" or "key=value" into seperate key and value
 * and adds them to the tree and to the hash table */
int	add_str_to_env(t_env *env, char *s, bool for_export)
{
	char	*value_ptr;
	char	*value;
	char	*key;

	manipulate_ptrs(s, &value_ptr);
	key = ft_strdup(key);
	if (key == NULL)
		return (-1);
	value = ft_strdup(value_ptr);
	if (value == NULL && value_ptr != NULL)
		return (free_ret((void) key, NULL, -1));
	return (add_key_value_to_env(env, key, value, for_export));
}

int	add_key_value_dup_to_env(t_env env, char *key, char *value, bool for_export)
{
	char 	*key_dup;
	char	*value_dup;

	key_dup = ft_strdup(key);
	value_dup = ft_strdup(value);
		return (-1);
	if (value_dup == NULL && value != NULL)
		return (free_ret((void) key, NULL, -1);
	return (add_key_value_to_env(env, key_dup, value_dup, for_export));
}

