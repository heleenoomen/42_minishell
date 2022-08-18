/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:23:30 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/18 12:00:51 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_node(t_tree_node *node, char *value, short flags)
{
	node->value = value;
	node->for_export = flags & EXPORT;
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
				return (-1);
		}
		else
			val_dup = value;
		free((*pos)->value);
		update_node(*pos, val_dup, flags);
	}
	return (0);
}

int update_env_node(t_tree_node *node, char *value, short flags)
{
	char	*val_dup;

	if (value == NULL)
		return (1);
	if (flags & VAL_OVERW)
	{
		if (ft_strdup_int(&val_dup, value) == -1)
			return (-1);
	}
	else
		val_dup = value;
	free(node->value);
	update_node(node, val_dup, flags & ~VAL_DUP);
	return (0);
}
	
