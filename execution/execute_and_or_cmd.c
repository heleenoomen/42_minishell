/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_or_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:58:52 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/13 14:15:55 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	reset_node(t_exec *exec)
{
	t_ast	*node;
	int		node_id;

	node = lst_get_cmd(*exec->cmds_list);
	node_id = node->node_id - 1;
	while (node && (node->node_id > node_id))
	{
		node = lst_get_content(exec->cmds_list);
		if (node->cmds)
			free_cmd_defs(&node->cmds);
		free(node);
		node = lst_get_cmd(*exec->cmds_list);
	}
}

int	execute_and_or_cmd(t_exec *exec, t_ast *node)
{
	t_node_type	node_type;
	int			last_status;
	int			status;

	last_status = exec->status;
	node_type = node->type;
	if (exec->fork)
	{
		waitpid(exec->pid, &status, 0);
		last_status = WEXITSTATUS(status);
		close(exec->pipe_fd[0]);
	}
	if (exec->fd_out > 1)
		close(exec->fd_out);
	if ((node_type == N_OR && !last_status) || (last_status && node_type == N_AND))
		reset_node(exec);
	exec->fork = 0;
	exec->status = last_status;
	g_global_exit_status = last_status;
	return (last_status);
}