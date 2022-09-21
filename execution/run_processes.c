/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:27:43 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/21 18:50:45 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_cmd_child(t_exec *exec, t_cmd_def *cmd, t_minishell *minishell) // Heleen: question for Kany: isn't t_cmd_def part of t_exec ? Why both params? I think I'm still confused which one to pass to the builtin checker. //
{
	char	**envp;
	char	*path;

	char *s = exec->cmd_type->cmd->content;  // goes to child process
	char *cpy = cmd->cmd->content; // goes to child process 
	dprintf(2, "run_cmd_child, s = %s, cpy = %s\n", s, cpy);
	close(exec->pipe_fd[0]);
	if (!builtin(cmd->cmd, minishell))
	{		
		dprintf(2, "runn_cmd_child, line 26\n");
		exec->curr_cmd = list_to_argv(cmd->cmd, NULL); /* put into array the list of cmds*/;
		dprintf(2, "argv[0] = %s\n", exec->curr_cmd[0]);
		dprintf(2, "run_cmd_child, line 28\n");
		envp = make_envp(minishell->env); /*get env */
		dprintf(2, "run_cmd_child, line 30\n");
		path = find_path(exec->curr_cmd[0], minishell->env); /* get path */
		dprintf(2, "run_cmd_child, line 30\n");
		if (exec->curr_cmd != NULL && envp != NULL && path != NULL)
		{
			dprintf(2, "run_cmd_chill, lin 32\n");
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
	dprintf(2, "in child_proces\n");
	char *s = exec->cmd_type->cmd->content;  // goes to child process
	char *cpy = cmd->cmd->content; // goes to child process 
	dprintf(2, "child_process, s = %s, cpy = %s\n", s, cpy);
	child_send_signal();
	//free_syntax_table(minishell->table);
	//free_ast_node(&cmd->cmd);
	/*clean history */
	dprintf(2, "exec->fd_in = %d, exec->fd_out = %d\n", exec->fd_in, exec->fd_out);
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
	int	pid;

	status = 0;
	char *s = exec_cmds->cmd_type->cmd->content;  // goes to child process
	char *cpy = cmds->cmd->content; // goes to child process 
	dprintf(2, "fork_process, s = %s, cpy = %s\n", s, cpy);
	if (pipe(exec_cmds->pipe_fd) == -1)
		status = 1;
	pid = fork();
	exec_cmds->pid = pid;
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
