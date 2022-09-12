/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:41:05 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/12 14:56:21 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "destroy.h"

void	free_ast_node(t_list **node)
{
	t_ast	*temp_node;
	t_list	*lst_node;

	if (node && *node)
	{
		lst_node = *node;
		while (ft_lstsize(lst_node))
		{
			temp_node = (t_ast *)lst_get_content(&lst_node);
			if (temp_node->cmds)
				free_ast_node(&temp_node->cmds);
			free(temp_node);
		}
		*node = NULL;
	}
}

void	free_ast_recurs(t_ast **node)
{
	if (!(*node))
		return ;
	ft_ast_cleaner(&(*node)->child);
	ft_ast_cleaner(&(*node)->next_sibling);
	ft_destroy_command(&(*node)->cmds);
	free(*node);
	*node = NULL;
}

void	free_full_ast(t_ast **ast)
{
	free_ast_recurs(ast);
	*ast = NULL;
}

void	free_cmd_defs(t_cmd_def **cmds)
{
	if (*cmds)
	{
		if ((*cmds)->cmd)
			ft_lstclear(&((*cmds)->cmd), &free);
		if ((*cmds)->redir)
			ft_lstclear(&((*cmds)->redir), &free);
		if ((*cmds)->assign)
			ft_lstclear(&((*cmds)->assign), &free);
		free(*cmds);
		*cmds = NULL;
	}
}