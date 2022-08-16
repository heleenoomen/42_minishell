/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:58:20 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 20:01:43 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree_node	*find_node(t_tree_node *root, char *key)
{
	int	ret;
	
	if (root == NULL)
		return (NULL);
	ret = ft_strcmp(key, root->key);
	if (ret == 0)
		return (root);
	if (ret < 0)
		return (find_node(root->left, key));
	return (find_node(root->right, key));
}

char	*get_value(t_tree_node *root, char *key)
{
	t_tree_node *node;

	node = find_node(root, key);
	if (node == NULL)
		return (NULL);
	return (node->value);
}

	
