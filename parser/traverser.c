/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:16:34 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/10 20:45:19 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	*create_new_node(t_grammar tok_type)
{
	t_parser	*node;

	node = malloc(sizeof(t_parser));
	node->token_type = tok_type;
	node->node_type = N_DUMM;
	node->node = NULL;
	return ((void *)node);
}

void	branch_node(t_parser **new_node, t_parser *old_node, int node_type)
{
	*new_node = create_new_node(type);
	(*new_node)->node = old_node->node;
}

void	branch_child_node(t_parser **new_node, t_parser *prev_node, int type)
{
	t_ast	*sibling;
	void	*new_temp;

	*new_node = create_new_node(type);
	new_temp = create_new_node(N_DUMM);
	sibling = add_child(prev_node->node, new_temp);
	(*new_node)->node = sibling;
	return (sibling);
}

void	*lst_get_content(t_list **lst)
{
	void	*content;
	t_list	*temp;

	content = NULL;
	if (lst && *lst)
	{
		temp = (*lst)->next;
		content = (*lst)->content;
		free(*lst);
		*lst = temp;
	}
	return (content);
}

void	*lst_get_cmd(t_list *cmd)
{
	if (cmd)
	{
		return (cmd->content);
	}
	return (NULL);
}
