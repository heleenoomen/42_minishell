/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:28:51 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/18 18:10:10 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* adds duplicated tree and value to the tree
 */
int	add_to_tree(t_env *env, char *key, char *value, short flags)
{
	t_tree_node *new;

	new = new_node(key, value, flags);
	if (new == NULL)
		return (-1);
	add_node(&(env->tree), new);
	env->size++;
	return (0);
}

/* adds a key value pair to env struct.Duplicates key and value if needed.
 */
int	add_key_value_to_env(t_env *env, char *key, char *value, short flags)
{
	char		*key_dup;
	char		*val_dup;
	
	if (flags & KEY_DUP)
	{
		if (ft_strdup_int(&key_dup, key) == -1)
			return (-1);
	}
	else
		key_dup = key;
	if (flags & VAL_DUP)
	{
		if (ft_strdup_int(&val_dup, value) == -1)
			return (del_key_value(key, NULL, flags, -1));
	}
	else
		val_dup = value;
	if (add_to_tree(env, key_dup, val_dup, flags) == -1)
		return (del_key_value(key, value, flags, -1));
	return (0);
}

/* searches for equal sign in s. If found, replaces it with '\0', sets value_ptr
 * (passed by referenc) to one byte after the equalsign and returns a pointer to 
 * the equalsign. If not found, sets value_pointer to NULL and returns NULL.
 */
char	*manipulate_ptrs(char *s, char **value_ptr)
{
	while (*s && *s != '=')
		s++;
	if (*s == '=')
	{
		*value_ptr = s + 1;
		*s = '\0';
		return (s);
	}
	*value_ptr = NULL;
	return (NULL);
}

/* takes a string s of type "KEY" or "KEY=VALUE" and manipulates ptrs so that s
 * becomes a nul terminated string to key and value_ptr becomes a pointer to value.
 * Calls add_key_value_to_env to add the elements to the environment struct.
 * Places back the equal sign if it was found. Returns 0 upon success, -1 if malloc fails.
 */
int	add_string_to_env(t_env *env, char *s, short flags)
{
	char	*value_ptr;
	char	*equalsign;
	int		ret;

	equalsign = manipulate_ptrs(s, &value_ptr);
	ret = add_key_value_to_env(env, s, value_ptr, flags | VAL_DUP | KEY_DUP);
	if (equalsign != NULL)
		*equalsign = '=';
	return (ret);
}

