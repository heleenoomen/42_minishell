/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cfg_definition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:42:54 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/13 18:28:12 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ast.h"

void	run_start(t_list **stack_table, t_grammar type)
{
	t_parser *node;
	t_parser *temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_and_or(t_list **stack_table, t_grammar type)
{
	t_parser *node;
	t_parser *temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, NT_AND_OR1);
		ft_lstpush(stack_table, node);
		branch_child_node(&node, temp_node, NT_PIPESPLIT);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_and_or1(t_list **stack_table, t_grammar type)
{
	t_parser *node;
	t_parser *temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		if (type == T_OR)
			temp_node->node->type = N_OR;
		else
			temp_node->node->type = N_AND;
		branch_child_node(&node, temp_node, NT_AND_OR);
		ft_lstpush(stack_table, node);
		branch_node(&node, temp_node, type);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	set_epsilon(t_list **stack_table, t_grammar type)
{
	t_parser *temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		free(temp_node);
	}
}

void	run_pipe(t_list **stack_table, t_grammar type)
{
	t_parser *node;
	t_parser *temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, NT_PIPESPLIT1);
		ft_lstpush(stack_table, node);
		branch_child_node(&node, temp_node, NT_COMMANDSET);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_pipe1(t_list **stack_table, t_grammar type)
{
	t_parser *node;
	t_parser *temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_child_node(&node, temp_node, NT_PIPESPLIT);
		ft_lstpush(stack_table, node);
		branch_node(&node, temp_node, type);
		node->node->type = N_PIPE;
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_subshell(t_list **stack_table, t_grammar type)
{
	t_parser *node;
	t_parser *temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		temp_node->node->type = NT_SUBSHELL;
		branch_node(&node, temp_node, T_RBRACE);
		ft_lstpush(stack_table, node);
		branch_child_node(&node, temp_node, NT_AND_OR);
		ft_lstpush(stack_table, node);
		branch_node(&node, temp_node, T_LBRACE);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_commandset(t_list **stack_table, t_grammar type)
{
	t_parser *node;
	t_parser *temp_node;

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
	
	t_parser *node;
	t_parser *temp_node;

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
	t_parser *node;
	t_parser *temp_node;

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

	if (tok_type >= 0)
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

void	run_io_file(t_list **stack_table, t_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		if (type == T_DLESS)
			branch_node(&node, temp_node, NT_IO_HERE);
		else
			branch_node(&node, temp_node, NT_IO_FILE)
		ft_lstpush(stack_table, node);
		free(temp_node)
	}
}
void	run_prefix_with_cmd(t_list **stack_table, t_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, NT_PREFIX);
		ft_lstpush(stack_table, node);
		if (type == T_ASSIGN)
		{
			branch_node(&node, temp_node, T_ASSIGN);
			node->node_type = N_ASSIGN;
		}
		else
			branch_node(&node, temp_node, T_ASSIGN);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_prefix_with_cmd1(t_list **stack_table, t_grammar type)
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

void	run_cmd_suffix(t_list **stack_table, t_grammar type)
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
			branch_node(&node, temp_node, NT_REDIR);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_cmd_suffix1(t_list **stack_table, t_grammar type)
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

void	redirect_to_file(t_list **stack_table, t_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, T_STRING);
		node->node_type = NT_REDIR;
		ft_lstpush(stack_table, node);
		branch_node(&node, temp_node, type),
		node->node_type = NT_REDIR;
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_redirections(t_list **stack_table, t_grammar type)
{
	t_parser	*node;
	t_parser	*temp_node;

	if (type >= 0)
	{
		temp_node = (t_parser *)lst_get_content(stack_table);
		branch_node(&node, temp_node, NT_REDIR1);
		ft_lstpush(stack_table, node);
		branch_node(&node, temp_node, NT_IO_REDIR);
		ft_lstpush(stack_table, node);
		free(temp_node);
	}
}

void	run_redirections1(t_list **stack_table, t_grammar type)
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






