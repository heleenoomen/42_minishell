/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverser_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:26:35 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/16 14:27:06 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	run_commandset(t_list **stack_table, t_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		temp_node->node->type = N_CMD;
		if (type == T_LBRACE)
		{
			branch_node(&node, temp_node, NT_CMD1);
			ft_lstpush(stack_table, node);
			branch_child_node(&node, temp_node, NT_SUBSHELL);
			ft_lstpush(stack_table, node);
		}
		else
		{
			branch_node(&node, temp_node, NT_CMD);
			ft_lstpush(stack_table, node);
		}
		free(temp_node);
	}
}

void	run_commandset1(t_list **stack_table, t_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, NT_REDIR);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_command(t_list **stack_table, t_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		if (type == T_STRING)
		{
			branch_node(&node, temp_node, NT_CMD2);
			ft_lstpush(stack_table, node);
			branch_node(&node, temp_node, T_STRING);
			node->node_type = N_CMD;
			ft_lstpush(stack_table, node);
		}
		else
		{
			branch_node(&node, temp_node, NT_CMD2);
			ft_lstpush(stack_table, node);
			branch_node(&node, temp_node, NT_PREFIX);
			ft_lstpush(stack_table, node);
		}
		free(temp_node);
	}
}

void	run_command1(t_list **stack_table, t_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(type);
		branch_node(&node, temp_node, NT_CMD2);
		ft_lstpush(stack_table, node);
		branch_node(&node, temp_node, T_STRING);
		node->node_type = N_CMD;
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_command2(t_list **stack_table, t_grammar type)
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