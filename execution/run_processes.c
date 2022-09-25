/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:27:43 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/25 19:14:01 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_cmd_child(t_exec *exec, t_cmd_def *cmd, t_minishell *minishell)
{
	char	**envp;
	char	*path;
	
	close(exec->pipe_fd[0]);
	if (!builtin_child_process(exec, cmd, minishell))
	{		
		exec->curr_cmd = list_to_argv(cmd->cmd, NULL);
		envp = make_envp(minishell->env);
		path = find_path(exec->curr_cmd[0], minishell->env);
		free_minishell(minishell);
		free_cmd_defs(&cmd);
		if (exec->curr_cmd != NULL && envp != NULL && path != NULL)
		{
			duplicate_fd(exec);
			if (execve(path, exec->curr_cmd, envp) == -1)
			{
				error_shell("exec failed", ERROR_PERROR);
				g_global_exit_status = 1;
			}
		}
		ft_freestrarr(&exec->curr_cmd);
		ft_freestrarr(&envp);
		free(path);
	}
	if (exec->fd_in > 0)
		close(exec->fd_in);
	close(exec->pipe_fd[1]);
	exit(g_global_exit_status);
}

int	child_process(t_exec *exec, t_cmd_def *cmd, t_minishell *minishell)
{
	int	status;

	status = 0;
	signals_child_process(&(minishell->termios_cpy));
	if (exec->fd_in >= 0 && exec->fd_out > 0)
		status = run_cmd_child(exec, cmd, minishell);
	else
	{
		close(exec->pipe_fd[0]);
		close(exec->pipe_fd[1]);
		free_cmd_defs(&cmd);
		free_minishell(minishell);
		if (exec->fd_in < 0 || exec->fd_out < 0)
			exit(g_global_exit_status);
		else
			exit(EXIT_SUCCESS);
	}
	return (status);
}

void	parent_process(t_exec *exec, t_cmd_def *cmd)
{
	t_ast	*node;

	signals_parent_process();
	node = lst_get_cmd(*exec->cmds_list);
	if (ft_lstsize(*exec->cmds_list) && cmd && cmd->cmd && \
		node->type != N_AND && node->type != N_OR)
		waitpid(exec->pid, NULL, 0);
	else
		waitpid(exec->pid, NULL, 1);
	close(exec->pipe_fd[1]);
	if (exec->fd_in > 0)
		close(exec->fd_in);
}

int	fork_process(t_exec *exec_cmds, t_cmd_def *cmds, t_minishell *minishell)
{
	int	status;

	if (cmds->cmd == NULL)
		return (0);
	status = 0;
	if (pipe(exec_cmds->pipe_fd) == -1)
		return(error_shell("Failed to create a pipe", ERROR_PERROR));
	exec_cmds->pid = fork();
	if (exec_cmds->pid == -1)
		status = error_shell("Failed to create a pipe", ERROR_PERROR);
	exec_cmds->forks = 1;
	if (exec_cmds->pid == 0 && status == 0)
		status = child_process(exec_cmds, cmds, minishell);
	parent_process(exec_cmds, cmds);
	return (status);
}
