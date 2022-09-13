/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:10:51 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/13 11:34:00 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* to existing parent node adds child node, if child node exists - 
assigns incoming to a next sibling */
t_ast	*add_child(t_ast *top, t_ast *child)
{
	t_ast	*sibling;

	if (!top || !child)
		return (NULL);
	if (!top->child)
		top->child = child;
	else
	{
		sibling = top->child;
		while (sibling->next_sibling)
			sibling = sibling->next_sibling;
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	top->nodes++;
	return (child);
}

void	free_node(t_ast *node)
{
	t_ast	*sibling;
	t_ast	*temp;

	if (node == NULL)
		return ;
	temp = node->child;
	while (temp)
	{
		sibling = temp->next_sibling;
		free_node(temp);
		temp = sibling;
	}
	if (node->cmds != NULL)
		free(node->cmds);
	free(node);
}

/* AST builder:
1. initializes the content and saves input line into t_prompt 
structure;
2. calls lexer function to receieve a list of tokens;
3. if a list of tokens exist, parses through syntax check is called;
Syntax check implements creation of nodes depending on the grammar 
and list of tokens.
*/

t_ast	*ast_builder(char *input, void (***table)(t_list **, t_grammar))
{
	t_prompt	content;
	t_ast		*node;
	t_list		*token_list;

	node = NULL;
	copy_input_line(&content, input);
	token_list = lexer(&content);
	if (token_list != NULL)
	{
		node = check_syntax(token_list, table);
		ft_lstclear(&token_list, &free_token);
	}
	return (node);
}
