/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:20:49 by kanykei           #+#    #+#             */
/*   Updated: 2022/09/06 11:31:18 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	child_process_heredoc(char *delim, int *fd, t_exec *exec, t_minishell *shell)
{
	int		nline;
	char	*get_line;
	char	*update_line;

	nline = shell->line_len;
	/*check heredoc error from nline later for end of function ?*/
	child_send_signal();
	/* free all structs and history*/
	close(fd[0]);
	update_line = NULL;
	ft_pustr_fd("heredoc>", 1)
	get_line = get_next_line(STDIN_FILENO);
	while (get_line)
	{
		update_line = ft_substr(get_line, 0, ft_strlen(get_line) - 1);
		if (ft_strcmp(delim, update_line) == 0)
			/*free line and delim */
		if (write(fd[1], get_line, ft_strlen(get_line)) == -1)
			/*error in pipe */
		/*free line and cmd stack */
		ft_pustr_fd("heredoc>", 1)
		get_line = get_next_line(STDIN_FILENO);
	}
	/* destructor for freeing everything */
}

int	execute_heredoc(char *delim, t_exec *exec, t_minishell *shell)
{
	int	status;
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		perror("Pipe failed"); /* error handling */
	parent_send_signal();
	pid = fork();
	if (pid == -1)
		status = /* error */
	if (pid == 0)
		child_process_heredoc(delim, fd, exec, shell);
	wait(&status);
	if (!WIFSGNALED(status))
		g_global_exit_status = WEXITSTATUS(status);
	close(fd[1]);
	if (g_global_exit_status == 0)
		dup2(fd[0], 0);
	else
		exec->fd_in = -1;
	close(fd[0]);
	return (g_global_exit_status);
}
