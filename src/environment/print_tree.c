/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:57:53 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 18:43:22 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_tree_node *root, int fd)
{
	if (root == NULL)
		return ;
	print_tree(root->left, fd);
	ft_putstr_fd(root->key, fd);
	write(fd, "\n", 1);
	print_tree(root->right, fd);
}

void	print_hash(t_env *env, int fd)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		ft_putstr_fd(env->env_hash[i].key, fd);
		write(fd, "\n", 1);
		i++;
	}
}
