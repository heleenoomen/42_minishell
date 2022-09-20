/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:55:04 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/27 15:22:31 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../ast.h"

// void	ft_print_recurs(t_ast *root, int space);
// void	ft_print_btree(t_ast *root);

// void	ft_print_recurs(t_ast *root, int space)
// {
// 	t_ast	*temp;
// 	int		i;

// 	if (root == NULL)
// 		return ;
// 	temp = root;
// 	space += 10;
// 	if (temp->next_sibling)
// 		ft_print_recurs(temp->next_sibling, space);
// 	printf("\n");
// 	i = 10;
// 	while (i < space)
// 	{
// 		printf(" ");
// 		i++;
// 	}
// 	printf("| %d |", *(int *)temp->type);
// 	if (temp->child)
// 		ft_print_recurs(temp->child, space);
// }

// void	ft_print_btree(t_ast *root)
// {
// 	ft_print_recurs(root, 0);
// }

void	remove_ast_node(t_ast **node)
{
	t_ast	*temp;

	if (*node != NULL)
	{
		remove_ast_node(&(*node)->next_sibling);
		remove_ast_node(&(*node)->child);
	}
	if (*node != NULL && (*node)->type != N_SUB && (*node)->nodes == 1)
	{
		temp = *node;
		*node = (*node)->child;
		(*node)->next_sibling = temp->next_sibling;
		(*node)->prev_sibling = temp->prev_sibling;
		free (temp);
	}
}

/*frees list of commands from the node */
void	free_ast_commands(t_cmd_def **cmds)
{
	if (*cmds == NULL)
		return ;
	if ((*cmds)->cmd)
		ft_lstclear(&((*cmds)->cmd), &free);
	if ((*cmds)->redir)
		ft_lstclear(&((*cmds)->redir), &free);
	if ((*cmds)->assign)
		ft_lstclear(&((*cmds)->assign), &free);
	free(*cmds);
	*cmds = NULL;
}

/* frees AST node by node */
void	free_ast_tree(t_ast **ast)
{
	if (*ast == NULL)
		return ;
	free_ast_tree(&(*ast)->child);
	free_ast_tree(&(*ast)->next_sibling);
	free_ast_commands(&(*ast)->cmds);
	free(*ast);
	*ast = NULL;
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

void	free_token(void *token)
{
	if (((t_token *)token)->input)
		free(((t_token *)token)->input);
	free(token);
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

t_ast	*init_new_node(t_node_type n_type)
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

void	init_parser(t_list **cmds_list, t_ast **node)
{
	*cmds_list = NULL;
	*node = init_new_node(N_DUMM);
	ft_lstpush(cmds_list, create_node(T_EOF));
	ft_lstpush(cmds_list, create_node(NT_START));
	((t_parser *)(*cmds_list)->content)->node = *node;
}

void	*lst_get_cmd(t_list *cmd)
{
	if (cmd)
	{
		return (cmd->content);
	}
	return (NULL);
}

void	add_nodes_parser(t_list **tokens, t_parser *node_p, t_list **cmd)
{
	t_list	*new;

	printf("Add nodes\n");
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

int	scan_nodes_parser(t_list *token_list, t_parser *node_p, \
t_list **cmds, void (***table)(t_list **, t_grammar))
{
	t_grammar	token_type;
	void		(*tab)(t_list **, t_grammar);
	int			flag;

	flag = 1;
	tab = NULL;
	token_type = ((t_token *)token_list->content)->type;
	printf("Scan: tok_type: %d\n", token_type);
	if (node_p->node_type < NONTERM)
	{
		tab = table[node_p->node_type][token_type - NONTERM];
		printf("TABLE: %d and %d\n", node_p->node_type, (token_type - NONTERM));
	}
	if (tab)
	{
		printf("In tab: %u\n", ((t_ast*)(*cmds)->content)->type);
		printf("In tab: %u\n", ((t_token *)token_list->content)->type);
		tab(cmds, ((t_token *)token_list->content)->type);
	}
	else
		flag = 0;
	if (!flag)
	{
		while (ft_lstsize(*cmds) > 0)
			free(lst_get_content(cmds));
	}
	return (flag);
}

t_ast	*check_syntax(t_list *token_list, void (***table)(t_list **, t_grammar))
{
	t_ast		*node;
	t_parser	*node_p;
	t_list		*cmds;
	int			flag;

	flag = 1;
	init_parser(&cmds, &node);
	while (flag && ft_lstsize(cmds) > 0)
	{
		printf("TOKEN: %s\n", ((t_token *)token_list->content)->input);
		node_p = (t_parser *)lst_get_cmd(cmds);
		if (((t_token *)token_list->content)->type == node_p->token_type)
			add_nodes_parser(&token_list, node_p, &cmds);
		else
		{
			flag = scan_nodes_parser(token_list, node_p, &cmds, table);
			printf("Flag: %d\n", flag);
		}
	}
	exit(0);
	if (!flag)
	{
		printf("Parse Error");
		free_ast_tree(&node);
	}
	remove_ast_node(&node);
	return (node);
}

t_ast	*ast_builder(char *input, void (***table)(t_list **, t_grammar))
{
	t_ast		*node;
	t_prompt	content;
	t_list		*token_list;

	node = NULL;
	copy_input_line(&content, input);
	token_list = lexer(&content);
	// while (token_list)
	// {
	// 	printf("%s - ", ((t_token*)token_list->content)->input);
	// 	printf("%u\n", ((t_token*)token_list->content)->type);
	// 	token_list = token_list->next;
	// }
	if (token_list)
	{
		node = check_syntax(token_list, table);
		printf("%d\n", node->nodes);
		printf("end\n");
		exit(0);
		// printf("%s\n", ((t_list *)node->cmds->redir)->content);
		ft_lstclear(&token_list, &free_token);
	}
	printf("END");
	// ft_print_btree(node);
	return (node);
}

void	launch_table(void (***table)(t_list **, t_grammar))
{
	int	i;
	int	j;

	i = 0;
	while (i < NONTERM)
	{
		j = 0;
		while (j < TOKENS)
		{
			table[i][j] = NULL;
			j++;
		}
		i++;
	}
	start_and_or(table);
	pipe_and_subshell(table);
	split_to_prefix(table);
	run_redirections_grand(table);
	commandset_and_io_here_file(table);
	get_suffix_cmd(table);
	child_commands(table);
}

void	init_minishell(t_minishell *shell)
{
	int	col;

	col = 0;
	shell->line_len = 0;
	shell->value = NULL;
	/*env */
	shell->table = malloc(NONTERM * sizeof(void***));
	while (col < NONTERM)
	{
		shell->table[col] = malloc(TOKENS * sizeof(void**));
		col++;
	}
	launch_table(shell->table);
}

int main(int argc, char **argv)
{
	t_prompt line;
	t_list	*lex;
	char *input;
	t_minishell	shell;
	t_ast	*root;

	input = argv[1];
	init_minishell(&shell);
	root = ast_builder(input, shell.table);
	printf("\n ___________________________ \n");
	return (0);
}
