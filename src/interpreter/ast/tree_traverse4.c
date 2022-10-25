/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_traverse4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:18:23 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/25 16:44:31 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	run_prefix_with_cmd(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, NT_PREFIX1);
		ft_lstpush(stack_table, node);
		if (type == T_ASSIGN)
		{
			branch_node(&node, temp_node, T_ASSIGN);
			node->node_type = N_ASSIGN;
		}
		else
			branch_node(&node, temp_node, NT_IO_REDIR);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_prefix_with_cmd1(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, NT_PREFIX);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_cmd_suffix(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, NT_SUFFIX1);
		ft_lstpush(stack_table, node);
		if (type == T_STRING)
		{
			branch_node(&node, temp_node, T_STRING);
			node->node_type = N_CMD;
		}
		else
			branch_node(&node, temp_node, NT_IO_REDIR);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_cmd_suffix1(t_list **stack_table, enum e_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, NT_SUFFIX);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}
