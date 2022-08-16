/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:37:36 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 19:55:18 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* updates an entry in env->env_hash when the value or export status of a
 * leaf in the tree was altered
 */
void	update_hash(t_env *env, t_tree_node *leaf)
{
	int	i;

	i = key_index(leaf->key);
	env->env_hash[i].value = leaf->value;
	env->env_hash[i].for_export = leaf->for_export;
}

int	update_value(t_env *env, t_tree_node *node, char *new_value, bool for_export)
{
	if (new_value != NULL)
	{
		free(node->value);
		node->value = new_value;
	}
	node->for_export = for_export;
	update_hash(env, leaf);
	return (0);
}

int update_value_dup(t_env *env, t_tree_node *node, char *new_value, bool for_export)
{
	char	*value_dup;

	value_dup = ft_strdup(new_value);
	if (value_dup == NULL && new_value != NULL);
		return (-1);
	return (update_value(env, node, value_dup, for_export));
}

