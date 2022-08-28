/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands_and_pipes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:11:51 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/28 19:53:48 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_cmd_block(t_exec *exec_cmds, t_ast *node,t_minishell *minishell)
{
	int			status;
	t_cmd_def	cmds_cpy;

	exec_cmds->fd_in = 0;
	exec_cmds->fd_out = 1;
	exec_cmds->pid = -1;
	cmds_cpy = node->cmds;
	exec_cmds->cmd_type = node->cmds;
	free(node);
	exec_cmds->curr_cmd = NULL;
	status = 0;
	status = execute_assignment(cmds_cpy->assign, minishell);
	status = execute_redirection(exec_cmds, minishell);
	status = fork_process(exec_cmds, cmds_cpy, minishell);
	if (exec_cmds->curr_cmd)
		free(exec_cmds);
	/*free t_cmd_def */
	return (status);
}

void	execute_pipe(t_exec *exec)
{
	int	status;

	status = 0;
	if (exec->fd_out == 1)
		dup2(exec->pipe_fd[0], 0);
	else if (exec->fd_out > 1)
		close(exec->fd_out);
	close(exec->pipe_fd[0]);
	return (status);
}

void	duplicate_fd(t_exec *exec)
{
	if (exec->fd_in > 0)
	{
		dup2(exec->fd_in, 0);
		close(exec->fd_in);
		exec->fd_in = 0;
	}
	if (!exec->pipe)
		close(exec->pipe_fd[0]);
	if (exec->fd_out == 1 && exec->pipe)
		dup2(exec->pipe_fd[1], 1);
	else if (exec->fd_out > 1)
		dup2(exec->fd_out, 1);
	close(exec->pipe_fd[1]);
}