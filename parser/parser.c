/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:02:41 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/18 16:01:31 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/* Creates a new node for parser and assigns a token type */
void	*create_node(t_grammar tok_type)
{
	t_parser	*node;

	node = malloc(sizeof(t_parser));
	node->token_type = tok_type;
	node->node_type = N_DUMM;
	node->node = NULL;
	return ((void *)node);
}

/* if node type is command, assignment or redirection, function creates 
a list of each type and saves into the node */
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
	new = ft_lstnew(ft_strdup(((t_token *)(*tokens)->content)->input));
	if (node_p->node_type == N_CMD)
		ft_lstadd_back(&node_p->node->cmds->cmd, new);
	if (node_p->node_type == N_ASSIGN)
		ft_lstadd_back(&node_p->node->cmds->assign, new);
	if (node_p->node_type == N_REDIR)
		ft_lstadd_back(&node_p->node->cmds->redir, new);
	*tokens = (*tokens)->next;
	free(lst_get_content(cmd));
}

/* scans node type and calls the production of nodes according
to ll1 table, if nodes token type is not valid returns the flag zero*/
int	scan_nodes_parser(t_list *token_list, t_parser *node_p, \
t_list **cmds, void (***table)(t_list **, t_grammar))
{
	int			flag;
	void		(*tab)(t_list **, t_grammar);
	t_grammar	token_type;

	flag = 1;
	tab = NULL;
	token_type = ((t_token *)token_list->content)->type;
	if (node_p->node_type < NONTERM)
		tab = table[node_p->node_type][token_type - NONTERM];
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

/* Through the syntax check with a given grammar table, parser launches 
the tree:
1. initialzes the parser structure;
2. scans the nodes and token lists into temporary table and compares/verifies 
existing tokens with grammar table;
3. add nodes if node of commands, assignment or redirection is found;
4. in case of error, frees the node of a tree */
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
		node_p = (t_parser *)lst_get_cmd(cmds);
		if (((t_token *)token_list->content)->type == node_p->token_type)
			add_nodes_parser(&token_list, node_p, &cmds);
		else
			flag = scan_nodes_parser(token_list, node_p, &cmds, table);
	}
	if (!flag)
	{
		perror("Parser: token not verified");
		free_ast_tree(&node);
	}
	remove_ast_node(&node);
	return (node);
}
