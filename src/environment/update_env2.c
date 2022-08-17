/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:23:30 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 12:51:08 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_node(t_tree_node *node, char *value, short flags)
{
	node->value = value;
	node->export = flags & EXPORT;
}

int	update_hash(t_env *env, char *key, char *value, short flags)
{
	int	i;

	i = 0;
	while (ft_strcmp(key, env->env_hash[i].key))
		i++;
	env->env_hash[i].value = value;
	env->env_hash[i].for_export = flags & EXPORT;
}

int update_env(t_env *env, char *key, char *value, short flags)
{
	t_tree_node	**pos;
	char		*val_dup;

	pos = position_in_tree(&(env->tree), key);
	if (pos == NULL)
		return (add_key_value_to_env(env, key, value, flags));
	else if (value != NULL || flags & VAL_OVERW)
	{
		if (flags & VAL_DUP)
		{
			if (ft_strdup_int(&val_dup, value) == -1)
				return (-1)
		}
		else
			val_dup = value;
		free((*pos)->value);
		update_node(*pos, value, flags);
		update_hash(env, key, value);
	}
	return (0);
}
