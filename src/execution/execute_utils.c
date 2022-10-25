/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:50:25 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/25 16:37:09 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_quotes(char *str)
{
	char	*removed;
	int		len;

	len = 0;
	if (str)
	{
		len = ft_strlen(str);
		if ((str[0] == '\"' || str[0] == '\''))
			removed = ft_substr(str, 1, len - 2);
		else
			removed = ft_strdup(str);
	}
	else
		removed = NULL;
	return (removed);
}

int	get_redirect_file(t_list **redir_list, char **file)
{
	t_list	*temp;
	void	*hold;
	int		status;

	status = 0;
	temp = ft_lstnew(ft_strdup((*redir_list)->content));
	filename_expansion(&temp);
	if (ft_lstsize(temp) > 1)
	{
		status = expansion_error((char *)(*redir_list)->content, ERROR_REDIR);
		ft_lstclear(&temp, &free);
		*file = NULL;
	}
	else
	{
		hold = (*redir_list)->content;
		(*redir_list)->content = temp->content;
		temp->content = hold;
		*file = remove_quotes((char *)(*redir_list)->content);
		ft_lstdelone(temp, &free);
	}
	return (status);
}

/*init the exec struct */
void	init_exec_struct(t_exec *exec, t_list **cmds_list)
{
	exec->cmds_list = cmds_list;
	exec->cmd_type = NULL;
	exec->curr_cmd = NULL;
	exec->status = 0;
	exec->pid = -1;
	exec->fd_in = 0;
	exec->fd_out = 1;
	exec->builtin = 0;
	exec->forks = 0;
}
