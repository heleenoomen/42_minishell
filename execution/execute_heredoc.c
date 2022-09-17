/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:20:49 by kanykei           #+#    #+#             */
/*   Updated: 2022/09/17 11:24:50 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process_heredoc(char *delim, int *fd, t_exec *exec, t_minishell *shell)
{
	//int	nline;
	char	*get_line;
	char	*update_line;

	//nline = shell->line_len;
	/*check heredoc error from nline later for end of function ?*/
	child_send_signal();
	heredoc_child_helper_destruction(exec, shell);
	close(fd[0]);
	update_line = NULL;
	ft_putstr_fd("heredoc>", 1);
	get_line = readline(STDIN_FILENO);
	while (get_line)
	{
		update_line = ft_substr(get_line, 0, ft_strlen(get_line) - 1);
		if (ft_strcmp(delim, update_line) == 0)
		{
			heredoc_helper_destruction(&update_line, &get_line, fd, exec);
			heredoc_helper_destruction2(delim, 0);
			
		}
		if (write(fd[1], get_line, ft_strlen(get_line)) == -1)
			error_shell("Failed to write into pipe", ERROR_UNDEFINED);
		heredoc_helper_destruction(&update_line, &get_line, NULL, exec);
		ft_putstr_fd("heredoc>", 1);
		get_line = readline(STDIN_FILENO);
	}
	heredoc_helper_destruction(&update_line, &get_line, fd, exec);
	heredoc_helper_destruction2(delim, 1);
}

int	execute_heredoc(char *delim, t_exec *exec, t_minishell *shell)
{
	int	status;
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		error_shell("Failed to create a pipe in heredoc", ERROR_PERROR);
	parent_send_signal();
	pid = fork();
	if (pid == -1)
		status = error_shell(NULL, ERROR_PERROR);
	if (pid == 0)
		child_process_heredoc(delim, fd, exec, shell);
	wait(&status);
	if (!WIFSIGNALED(status))
		g_global_exit_status = WEXITSTATUS(status);
	close(fd[1]);
	if (g_global_exit_status == 0)
		dup2(fd[0], 0);
	else
		exec->fd_in = -1;
	close(fd[0]);
	return (g_global_exit_status);
}
