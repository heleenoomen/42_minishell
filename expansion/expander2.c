/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:21:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/26 14:06:54 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* expands a single string. Expands dollar sign, expands tilde and 
 * removes quotes if quote_removal is set.
 */
static char	*expand_string(char *s, t_env *env, int redir)
{
	t_char_buf	buf;
	char		*ret;

	init_char_buf(&buf);
	if (buf.buf == NULL)
		return (NULL);
	expand_dollarsign(env, s, &buf);
	if (buf.buf != NULL)
		expand_tilde(env, &buf);
	if (buf.buf != NULL && !redir)
	 	exp_remove_quotes(&buf);
	ret = ft_strdup(buf.buf);
	free(buf.buf);
	return (ret);
}

int	exp_remove_quotes_redir(t_list *lst_of_strings)
{
	t_list		*current;
	char		*new_content;
	t_char_buf	buf;

	init_char_buf(&buf);
	if (buf.buf == NULL)
		return (-1);
	current = lst_of_strings;
	while (current != NULL)
	{
		ft_strlcpy(buf.buf, current->content, ft_strlen(current->content));
		exp_remove_quotes(&buf);
		new_content = ft_strdup(buf.buf);
		if (buf.buf != NULL && new_content == NULL)
		{
			free(buf.buf);
			return (-1); 
		}
		free(current->content);
		current->content = new_content;
		ft_memset(buf.buf, 0, ft_strlen(buf.buf));
		current = current->next;
	}
	free(buf.buf);
	return (0);
}

/** traverses the list and expands all of its contents */
int	expand_list(t_list *lst_of_strings, t_env *env, int redir, int error_flag)
{
	t_list	*trav;
	char	*new_content;

	trav = lst_of_strings;
	while (trav != NULL)
	{
		if (redir)
			printf("%s\n", trav->content);
		new_content = expand_string(trav->content, env, redir);
		if (redir)
			filename_expansion(&trav);
		if (new_content == NULL)
		{
			g_global_exit_status = ENOMEM;
			expansion_error(lst_of_strings->content, error_flag);
			return (1);	
		}
		free(trav->content);
		trav->content = (void *) new_content;
		trav = trav->next;
	}
	return (0);
	trav = lst_of_strings;
	if (redir)
	{
		printf("%s\n", trav->content);
		filename_expansion(&lst_of_strings);
		return (0);
		if (exp_remove_quotes_redir(lst_of_strings))
			return (1);
	}
	return (0);
}

/** goes through the list of t_ast nodes. For every nodes, checks if the *cmds pointer is not
 * NULL. If it is not NULL, checks for every pointer in the t_cmd_def struct if the pointers to
 * *cmd, *redir and *assign are not NULL. If they are not NULL, calls expand_list to expand the nodes
 * in the list
 **/ 
int	expander(t_list *nodes, t_env *env)
{
	t_list	*ptr;
	t_ast	*current;
	int		status;

	ptr = nodes;
	status = 0;
	while (ptr != NULL && !status)
	{
		current = ptr->content;
		if (current->cmds)
		{
			if (current->cmds->cmd && !status)
				status = expand_list(current->cmds->cmd, env, true, ERROR_CMD);
			if (current->cmds->redir && !status)
				status = expand_list(current->cmds->redir, env, false, ERROR_REDIR);
			if (current->cmds->assign && !status)
				status = expand_list(current->cmds->assign, env, true, ERROR_CMD);
		}
		ptr = ptr->next;
	}
	return (status);
}

