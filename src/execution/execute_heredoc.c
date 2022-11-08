/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:20:49 by kanykei           #+#    #+#             */
/*   Updated: 2022/11/08 12:14:15 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process_heredoc(char *delim, int *fd, \
	t_exec *exec, t_minishell *shell)
{
	char	*get_line;
	char	*update_line;

	signals_child_heredoc();
	close(fd[0]);
	update_line = NULL;
	ft_putstr_fd("> ", 1);
	get_line = expand_here(shell->env, get_next_line(STDIN_FILENO));
	while (1)
	{
		if (get_line == NULL)
			heredoc_helper_destruction2(delim, 0);
		update_line = ft_substr(get_line, 0, ft_strlen(get_line) - 1);
		if (ft_strcmp(delim, update_line) == 0)
			heredoc_helper_destruction2(delim, 0);
		if (write(fd[1], get_line, ft_strlen(get_line)) == -1)
			error_shell("Failed to write into pipe", ERROR_UNDEFINED);
		heredoc_helper_destruction(&update_line, &get_line, NULL, exec);
		ft_putstr_fd("> ", 1);
		get_line = expand_here(shell->env, get_next_line(STDIN_FILENO));
	}
}

static void	heredoc_helper_delim(char *delim)
{
	if (delim[0] != '*')
		free(delim);
}

int	execute_heredoc(char *delim, t_exec *exec, t_minishell *shell)
{
	int	status;
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		error_shell("Failed to create a pipe in heredoc", ERROR_PERROR);
	signals_parent_process();
	pid = fork();
	if (pid == -1)
		error_shell(NULL, ERROR_PERROR);
	if (pid == 0)
		child_process_heredoc(delim, fd, exec, shell);
	wait(&status);
	if (!WIFSIGNALED(status))
		g_global_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_global_exit_status = 1;
	close(fd[1]);
	if (g_global_exit_status == 0)
		dup2(fd[0], 0);
	else
		exec->fd_in = -1;
	heredoc_helper_delim(delim);
	close(fd[0]);
	return (g_global_exit_status);
}
