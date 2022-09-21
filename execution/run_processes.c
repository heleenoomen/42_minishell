/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:27:43 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/21 19:10:39 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_cmd_child(t_exec *exec, t_cmd_def *cmd, t_minishell *minishell) // Heleen: question for Kany: isn't t_cmd_def part of t_exec ? Why both params? I think I'm still confused which one to pass to the builtin checker. //
{
	char	**envp;
	char	*path;

	close(exec->pipe_fd[0]);
	if (!builtin(cmd->cmd, minishell))
	{		
		exec->curr_cmd = list_to_argv(cmd->cmd, NULL); /* put into array the list of cmds*/;
		envp = make_envp(minishell->env); /*get env */
		path = find_path(exec->curr_cmd[0], minishell->env); /* get path */
		if (!builtin(cmd->cmd, minishell) && exec->curr_cmd != NULL && envp != NULL && path != NULL)
		{
			duplicate_fd(exec);
			if (execve(path, exec->curr_cmd, envp) == -1)
				error_shell("exec failed", ERROR_PERROR);
			ft_freestrarr(&exec->curr_cmd);
			ft_freestrarr(&envp);
			free(path);
		}
	}
	if (exec->fd_in > 0)
		close(exec->fd_in);
	close(exec->pipe_fd[1]);
	free_cmd_defs(&cmd);
	free_minishell(minishell);
	exit(g_global_exit_status);
}

int	child_process(t_exec *exec, t_cmd_def *cmd, t_minishell *minishell)
{
	int	status;

	status = 0;
	child_send_signal();
	free_syntax_table(minishell->table);
	free_ast_node(&cmd->cmd);
	/*clean history */
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

	status = 0;
	if (pipe(exec_cmds->pipe_fd) == -1)
		status = 1;
	exec_cmds->pid = fork();
	if (exec_cmds->pid == -1)
		status = error_shell("Failed to create a pipe", ERROR_PERROR);
	if (status == 0)
		exec_cmds->forks = 1;
	parent_send_signal();
	if (exec_cmds->pid == 0 && status == 0)
		status = child_process(exec_cmds, cmds, minishell);
	parent_process(exec_cmds, cmds);
	return (status);
}
