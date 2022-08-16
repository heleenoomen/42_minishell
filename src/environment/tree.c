/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 12:36:03 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 13:16:19 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_env_hash **descend_tree(t_env_hash *branch, char *key)
{
	if (branch == NULL)
		return (&(branch));
	if (branch->entry == NULL)
		return (&(branch->left));
	if (ft_strcmp(key, branch->entry->key) < 0)
		return (descend_tree(branch->left, key);
	return (descend_tree(branch->right, key);
}

void	add_to_tree(t_env *env, int i)
{
	t_tree_node	*new;
	t_tree_node *branch;
	t_env_hash	**leaf;

	new = malloc(sizeof(t_tree_node));
	new->entry = env->env_hash + i;
	new->left = NULL;
	new->right = NULL;
	branch = &env->tree;
	leaf = descend_tree(branch, env->env_hash[i]);
	*leaf = new;
}
