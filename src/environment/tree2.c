/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:06:20 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 13:04:01 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* returns the address where a new node should be inserted, based on the key
 * of the new node. If the key already exists, it returns the address of the 
 * node which contains the existing key. If the node does not exist, it returns
 * the address of a NULL pointer that should be set to point to the new node.
 */
t_env_tree	**position_in_tree(t_env_tree **tree, char *key)
{
	int	ret;
	if (*tree == NULL)
		return (tree);
	ret = ft_strcmp(key, (*tree)->value);
	if (ret == 0)
		return (tree);
	if (ret < 0)
		return (insert_position(&((*tree)->left), key);
	return (insert_position(&((*tree)->right), key);
}

/* makes a new node based on a key value pair. Key and value should already be
 * stored dynamically
 */
t_env_tree *new_node(char *key, char *value, short flags)
{
	t_env_tree	*new;

	new = malloc(sizeof(t_env_tree);
	if (new == NULL)
		return (NULL);
	new->key = key;
	new->value = value;
	new->export = flags & EXPORT;
	new->left = NULL;
	new->right = NULL;
}

/* adds a new node into the tree
 */
void	add_node(t_env_tree **tree, t_env_tree *new)
{
	*(position_in_tree(tree, new->key)) = new;
}

/* deletes a given node and frees all memory associated with it. Reinserts sub trees 
 * starting at the deleted node back into the tree.
 * Takes as a parameter the node to be deleted. If node = NULL, searches for the node
 * to be deleted based on the key parameter
 */
int	del_tree_node(t_env_tree **tree, t_env_tree **node, char *key, int ret)
{
	t_env_node	*left;
	t_env_node	*right;
	t_env_node	*free;	
	
	if (node == NULL)
		to_free = *(position_in_tree(tree, key));
	else
		to_free = *node;
	if (to_free == NULL)
		return (ret);
	left = to_free->left;
	right = to_free->right;
	free(to_free->key);
	to_free->key = NULL;
	free(to_free->value);
	to_free->value = NULL;
	free(to_free);
	*node = NULL;
	if (left != NULL)
		*(position_in_tree(tree, left)) = left;
	if (rigth != NULL)
		*(position_in_tree(tree, right)) = right;
	return (ret);
}

