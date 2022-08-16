/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:57:53 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 18:59:45 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_env_tree *root, int fd)
{
	if (root == NULL)
		return ;
	print_tree(root->left, fd);
	print_tree(root->right, fd);
	ft_putstr_fd(root->key, fd);
	write(fd, "\n", 1);
}
