/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:24:26 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/08 19:45:59 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_redirect_in(char *file, int	*fd)
{
	int	status;

	status = 0;
	if (*fd > 0)
		close(*fd);
	if (file != NULL)
	{
		*fd = open(file, O_RDONLY);
		if (*fd < 0)
		{
			status = 1;
			g_global_exit_status = status;
		}
	}
	if (status)
		perror("In redirection failure");
	return (status);
}

void	execute_redirect_overwrite(char *file, int	*fd)
{
	int	status;

	status = 0;
	if (*fd > 1)
		close(*fd);
	if (file != NULL)
	{
		*fd = open( file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (*fd < 0)
		{
			status = 1;
			g_global_exit_status = status;
		}
	}
	if (status)
		perror("Overwrite redirection failure");
	return (status);
}

void	execute_redirect_append(char *file, int	*fd)
{
	int	status;

	status = 0;
	if (*fd > 1)
		close(*fd);
	if (file != NULL)
	{
		*fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0664);
		if (*fd < 0)
		{
			status = 1;
			g_global_exit_status = status;
		}
	}
	if (status)
		perror("Append redirection failure");
	return (status);
}

void	execute_redirect_inout(char *file, int	*fd_in, int *fd_out)
{
	int	status;

	status = 0;
	if (file != NULL)
	{
		if (*fd_out > 1)
			close(*fd_out);
		*fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0664);
		if (*fd_out > 1)
			close(*fd_out);
		*fd_in = open(file, O_RDONLY);
	}
	if (*fd_out < 0 || *fd_in < 0)
	{
			status = 1;
			g_global_exit_status = status;
	}
	if (status)
		perror("In and Out redirection failure");
	return (status);
}

void	get_redirect_file(t_list **redir_list, char **file)
{
	t_list	*temp;
	void	*hold;
	int		status;

	status = 0;
	temp = ft_lstnew(ft_strdup(*redir_list)->content);
	filename_expansion(&temp);
	if (ft_lstsize(temp) <= 1)
	{
		hold = *redir_list->content;
		*redir_list->content = temp->content;
		new->content = hold;
		*file = remove_quotes((char *)(*redir_list)->content);
		ft_lstdelone(temp, &free);
	}
	else
	{
		status = /*error */
		ft_lstclear(&temp, &free);
	}
	return (status);
}

void	execute_redirection(t_exec	*exec, t_minishell *minishell)
{
	t_list	*redir;
	char	*file;
	int		status;

	status = 0;
	redir = exec->cmd_type->redir;
	while (redir && status == 0)
	{
		status = get_redirect_file(&redir->next, &file);
		if (!status && ft_strcmp((char *)redir->content, "<") == 0)
			status = execute_redirect_in(file, &exec->fd_in);
		else if (!status && ft_strcmp((char *)redir->content, ">") == 0)
			status = execute_redirect_overwrite(file, &exec->fd_out);
		else if (!status && ft_strcmp((char *)redir->content, ">>") == 0)
			status = execute_redirect_append(file, &exec->fd_out);
		else if (!status && ft_strcmp((char *)redir->content, "<<") == 0)
			status = execute_heredoc(file, exec, minishell);
		else if (!status && ft_strcmp((char *)redir->content, "<>") == 0)
			status = execute_inout(file, &exec->fd_in, &exec->fd_out);
		if (redir->next)
			redir = redir->next;
		free(file);
	}
	return (status);
}
