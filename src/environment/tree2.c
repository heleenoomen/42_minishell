/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:06:20 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 18:01:26 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* returns the address where a new node should be inserted, based on the key
 * of the new node. If the key already exists, it returns the address of the 
 * node which contains the existing key. If the node does not exist, it returns
 * the address of a NULL pointer that should be set to point to the new node.
 */
t_tree_node	**position_in_tree(t_tree_node **tree, char *key)
{
	int	ret;
	if (*tree == NULL)
		return (tree);
	ret = ft_strcmp(key, (*tree)->key);
	if (ret == 0)
		return (tree);
	if (ret < 0)
		return (position_in_tree(&((*tree)->left), key));
	return (position_in_tree(&((*tree)->right), key));
}

/* makes a new node based on a key value pair. Key and value should already be
 * stored dynamically
 */
t_tree_node	*new_node(char *key, char *value, short flags)
{
	t_tree_node	*new;

	new = malloc(sizeof(t_tree_node));
	if (new == NULL)
		return (NULL);
	new->key = key;
	new->value = value;
	new->for_export = flags & EXPORT;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

/* adds a new node into the tree
 */
void	add_node(t_tree_node **tree, t_tree_node *new)
{
	*(position_in_tree(tree, new->key)) = new;
}

/* deletes a given node and frees all memory associated with it. Reinserts sub trees 
 * starting at the deleted node back into the tree.
 * Takes as a parameter the node to be deleted. If node = NULL, searches for the node
 * to be deleted based on the key parameter
 * Returns 0 upon success, 1 if the node was not found
 */
int	del_tree_node(t_tree_node **tree, t_tree_node **node, char *key, int ret)
{
	t_tree_node	*left;
	t_tree_node	*right;
	t_tree_node	*to_free;	
	
	if (node == NULL)
		to_free = *(position_in_tree(tree, key));
	else
		to_free = *node;
	if (to_free == NULL)
		return (1);
	left = to_free->left;
	right = to_free->right;
	free(to_free->key);
	to_free->key = NULL;
	free(to_free->value);
	to_free->value = NULL;
	free(to_free);
	*node = NULL;
	if (left != NULL)
		*(position_in_tree(tree, left->key)) = left;
	if (right != NULL)
		*(position_in_tree(tree, right->key)) = right;
	return (ret);
}

/* frees whole tree and sets the pointer to the tree to NULL
 */
void	free_tree(t_tree_node **tree)
{
	t_tree_node	*node;

	node = *tree;
	if (node == NULL)
		return ;
	//ft_putstr_fd(node->key, 2);
	//write(2, "\n", 2);
	free_tree(&(node->left));
	free_tree(&(node->right));
	free(node->key);
	free(node->value);
	free(node);
	*tree = NULL;
}

