/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 17:02:28 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/17 17:00:49 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/* get nodes from tree into the ordered linked lists */
void	get_tree(t_list **nodes, t_ast *tree, int node_id)
{
	tree->node_id = node_id;
	if (tree->child)
		get_tree(nodes, tree->child->next_sibling, node_id++);
	if (tree->type != N_SUB)
		ft_lstpush(nodes, tree);
	get_tree(nodes, tree->child, node_id++);
	if (tree->type == N_SUB)
		ft_lstpush(nodes, tree);
}

void	execute_cmds_and_builtins(t_exec *exec_cmds, t_ast **node, t_minishell *minishell)
{
	t_ast *temp;

	exec_cmds->pipe = 0;
	temp = (t_ast *)lst_get_content(*exec_cmds->cmds_list);
	if (temp && temp->type == N_PIPE)
		exec_cmds->pipe = 1;
	exec_cmds->cmds_list = exec_cmds->cmds_list;
	if ((*node)->cmds->cmd && (*node)->cmds->cmd->content && /*check string if it is builtin*/)
		/*execute builtin */
	else
		/*execute commands */
	*node = NULL;
}

int	execute_commands(t_exec *exec_cmds, t_minishell *minishell)
{
	int		status;
	t_ast	*node;
	int		total_cmds;

	status = 0;
	total_cmds = ft_lstsize(*exec_cmds->cmds_list);
	while (status = 0 && exec_cmds->cmds_list && total_cmds >= 0)
	{
		node = (t_ast *)lst_get_content(exec_cmds->cmds_list);
		if (node->type == N_CMD && minishell)
			execute_cmd_builtin(exec_cmds, &node, minishell)
		else if (node->type == N_PIPE)
			status = /* run pipe */
		else if (node->type == N_AND || node->type == N_OR)
			/* run and or*/
		if (node)
		{
			if (node->cmd_type)
				/* free list of commands */
			free(node);
		}
	}
	if (exec_cmds->forks)
		close(exec_cmds->pipe[0]);
	return (status);
}

void	init_exec_struct(t_exec *exec, t_list **cmds_list)
{
	exec->cmds_list = cmds_list;
	exec->status = 0;
	exec->pid = -1;
	exec->fd_in = 0;
	exec->fd_out = 1;
	exec->builtin = 0;
	exec->forks = 0;
}

/* initialization of exec structure and passing list of nodes for 
actual execution
- if list of nodes is 1 -> single builtin is called
- if more nodes, execution of commands verify node type and call
functios according to operator 
- if something goes wrong, lists are free and status 1 is returned -> SET GLOBAL STATUS*/
int	start_execution(t_list **nodes, t_minishell *minishell)
{
	int		status;
	int		fd_temp;
	int		total_cmds;
	t_exec	exec_cmds;
	
	status = 0;
	fd_temp = dup(0);
	init_exec_struct(&exec_cmds, node);
	total_cmds = ft_lstsize(*nodes);
	if (total_cmds == 1)
		/* status = single builtin */
	status = execute_commands(&exec_cmds, minishell);
	if (status != 0 && t_lstsize(*nodes))
		/* free all nodes of lists */
	if (exec_cmds.forks && (!exec_cmds.builtin || total_cmds > 1))
	{
		waitpid(exec_cmds.pid, status, NULL);
		if (!WIFSIGNALED(status))
			g_global_exit_status = WEXITSTATUS(status);
	}
	dup2(fd_temp, 0);
	close(fd_temp);
	if (exec_cmds.fd_out > 1)
		close(exec_cmds.fd_out);
	return (status);
}

/* main execution function */
int	main_executor(char *readline, t_minishell *minishell)
{
	int		status;
	t_list	*nodes;
	t_ast	*tree;

	status = 0;
	node = NULL;
	tree = ast_builder(readline, minishell->table);
	if (tree)
	{
		get_tree(&nodes, tree, 0);
		// expand variables //
		start_execution(&node, minishell);
	}
	else
		status = 1;
	return (status);
}
