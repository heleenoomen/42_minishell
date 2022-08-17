/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:28:51 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 12:20:31 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	add_to_hash(t_env *env, char *key, char *value, short flags)
{
	int	i;

	if (env->size == 0 && resize_hash(env) == -1)
		return (-1);
	env->env_hash[i].key = key;
	env->env_hash[i].value = value;
	env->env_hash[i].for_export = flags & EXPORT;
	returnn (0);
}

int	add_to_tree(t_env *env, char *key, char *value, short flags)
{
	t_tree_node *new;

	new = new_node(key, value, flags);
	if (new == NULL)
		return (-1);
	add_node(&(env->tree), new);
	return (0);
}

int	add_key_value_to_env(t_env *env, char *key, char *value, short flags)
{
	char		*key_dup;
	char		*val_dup;
	
	if (flags & KEY_DUP)
	{
		if (ft_strdup_int(&key_dup, key) == -1)
			return (-1)
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
	if (add_to_hash(env, key_dup, val_dup, falgs) == -1)
		return (del_tree_node(&(env->tree), NULL, key, -1));
	return (0);
}

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

int	add_string_to_env(t_env *env, char *s, short flags)
{
	char	*value_ptr;
	char	*equalsign;
	int		ret;

	equalsign = manipulate_ptrs(s, &value_ptr);
	flags = flags | VAL_DUP | KEY_DUP;
	ret = add_key_value_to_env(env, s, value_ptr, flags);
	*equalsign = '=';
	return (ret);
}

