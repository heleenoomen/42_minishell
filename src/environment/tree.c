/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 12:36:03 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 18:59:57 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* descends the tree starting from branch and returns the address of a branch 
 * where a node should be inserted
 */
t_env_tree **descend_tree(t_env_tree **branch, char *key)
{
	int			ret;
	t_env_tree	*current;
	
	current = *branch
	if (current == NULL)
		return (branch);
	ret = ft_strcmp(key, current->key);
	if (ret == 0)
		return (branch);
	if (ret < 0)
		return (descend_tree(&(current->left), key);
	return (descend_tree(&(current->right), key);
}

/* creates a new node for a new key value pair
 */
t_env_tree *new_tree_node(char *key, char *value, bool for_export)
{
	t_env_tree	*new;

	new = malloc(sizeof(t_env_tree));
	if (new == NULL)
		return (NULL);
	new->key = key;
	new->value = value;
	new->for_export = for_export;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

/* changes the value or export status of a key that already exists
 */
void	change_value_and_or_export(t_env_tree **leaf, char *key, char *value, bool for_export)
{
	free(key);
	if (value != NULL)
	{
		free((*leaf)->value);
		(*leaf)->value = value;
	}
	(*leaf)->export = for_export;
}

/* (re-) inserts an existing node back into a tree
 */
void	tree_insert(t_env_tree **root, t_env_tree *node)
{
	t_env_tree	**insert;

	insert = descend_tree(root, node->key);
	*insert = node;
}

void	clear_node(t_env_tree **root, t_env_tree **branch, char *key)
{
	int			ret;
	t_env_tree	*left;
	t_env_tree	*right;
	
	if (branch == NULL)
		return ;
	ret = ft_strcmp(key, (*branch)->key);
	if (ret == 0)
	{
		left = (*branch)->left;
		right = (*branch)->right;
		free((*branch)->key);
		free((*branch)->value);
		free(*branch);
		*branch = NULL;
		tree_insert(root, left);
		tree_insert(root, right);
	}
	else if (ret < 0)
		clear_node(root, &((*branch)->left), key);
	else
		clear_node(root, &((*branch)->right), key);
}

