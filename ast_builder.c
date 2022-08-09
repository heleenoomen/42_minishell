/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 07:42:23 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/09 11:09:39 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "ast.h"

/*free node */

void	*lst_get_cmd(t_list *cmd)
{
	if (cmd)
	{
		return (cmd->content);
	}
	return (NULL);
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

void	add_nodes_parser(t_list **tokens, t_parser *node_p, t_list **cmd)
{
	t_list	*new;

	if (node_p->node && node_p->node->cmds == NULL && \
	(node_p->node_type == N_CMD || node_p->node_type == N_ASSIGN \
	|| node_p->node_type == N_REDIR))
	{
		node_p->node->cmds = malloc(sizeof(t_cmd_def));
		node_p->node->cmds->cmd = NULL;
		node_p->node->cmds->assign = NULL;
		node_p->node->cmds->redir = NULL;
	}
	new = ft_lstnew(ft_strdup(((t_token *)(*tokens)->content)->line));
	if (node_p->node_type == N_CMD)
		ft_lstadd_back(&node_p->node->cmds->cmd, new);
	if (node_p->node_type == N_ASSIGN)
		ft_lstadd_back(&node_p->node->cmds->assign, new);
	if (node_p->node_type == N_REDIR)
		ft_lstadd_back(&node_p->node->cmds->redir, new);
	tokens = (*tokens)->next;
	free(lst_get_content(cmd));
}

int	scan_nodes_parser(t_list *token_list, t_parser *node_p, \
t_list **cmds, void (***table)(t_list **, t_grammar))
{
	int			flag;
	void		(*tab)(t_list **, t_grammar);
	t_grammar	token_type;

	flag = 1;
	tab = NULL;
	token_type = ((t_token *)token_list->content)->type;
	if (node_p->node_type < TOK_KEYS)
		tab = table[node_p->node_type][token_type - TOK_KEYS];
	if (tab != NULL)
		tab(cmds, ((t_token *)token_list->content)->type);
	else
		flag = 0;
	if (flag == 0)
	{
		while (ft_lstsize(*cmds) > 0)
			free(lst_get_content(cmds));
	}
	return (flag);
}

void	remove_ast_node(t_ast **node)
{
	t_ast	*temp;

	if (*node != NULL)
	{
		remove_ast_node(&(*node)->next_sibling);
		remove_ast_node(&(*node)->child);
	}
	if (*node != NULL && (*node)->type != N_SUB && (*ast)->nodes == 1)
	{
		temp = *node;
		*node = (*node)->child;
		(*node)->next_sibling = temp->next_sibling;
		(*node)->prev_sibling = temp->prev_sibling;
		free (temp);
	}
}

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

t_ast	*init_new_node(t_node__type n_type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = n_type;
	node->cmds = NULL;
	node->nodes = 0;
	node->child = NULL;
	node->prev_sibling = NULL;
	node->next_sibling = NULL;
	return (node);
}

void	*create_node(t_grammar tok_type)
{
	t_parser	*node;

	node = malloc(sizeof(t_parser));
	node->token_type = tok_type;
	node->node_type = N_DUMM;
	node->node = NULL;
	return ((void *)node);
}

void	init_parse(t_list **cmds_list, t_ast **node)
{
	*cmds_list = NULL;
	*node = init_new_node(N_DUMM);
	ft_lstpush(cmds_list, create_node(T_EOF));
	ft_lstpush(cmds_list, create_node(TK_START));
	((t_parser *)(*cmds_list)->content)->node = *ast;
}

t_ast	*check_syntax(t_list *token_list, void (***table)(t_list **, t_grammar))
{
	t_ast		*node;
	t_parser	*node_p;
	t_list		*cmds;
	int			flag;

	init_parser(&cmds, &node);
	flag = 1;
	while (flag && ft_lstsize(cmds) > 0)
	{
		node_p = (t_parser *)get_cmd(cmds);
		if (((t_token *)token_list->content)->type == node_p->token_type)
			add_nodes_parser(&token_list, node_p, &cmds);
		else
			flag = scan_nodes_parser(token_list, node_p, &cmds, table);
	}
	if (flag == 0)
	{
		perror("Parser: token not verified");
		/* destroy ast */
	}
	remove_ast_node(&ast);
	return (ast);
}

void	init_content(t_prompt *content, char *input)
{
	content->input = ft_strdup(input);
	content->len = ft_strlen(input);
	content->index = -2;
}

t_ast	*ast_builder(char *input, void (***table)(t_list **, t_grammar))
{
	t_ast		*node;
	t_prompt	content;
	t_list		*token_list;

	node = NULL;
	init_content(&content, input);
	token_list = lexer(&content);
	if (token_list != NULL)
	{
		node = check_syntax(token_list, table);
		ft_lstclear(&token_list, &delete_token);
	}
	return (node);
}
