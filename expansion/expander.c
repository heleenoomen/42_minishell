/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:21:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/06 11:12:41 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* expands a single string. Expands dollar sign, expands tilde if tilde_exp is set
 * and removes quotes if quote_removal is set.
 */
static char	*expand_string(char *s, t_env *env)
{
	t_char_buf	buf;
	char		*ret;

	init_char_buf(&buf);
	if (buf.buf == NULL)
		return (NULL);
	expand_dollarsign(env, s, &buf);
	if (buf.buf != NULL)
		expand_tilde(env, &buf);
	if (buf.buf != NULL)
		remove_quotes(&buf);
	ret = ft_strdup(buf.buf);
	free(buf.buf);
	return (ret);
}

/** traverses the list and expands all of its contents */
void	expand_list(t_list *lst_of_strings, t_env *env)
{
	t_list	*trav;
	char	*new_content;

	if (t_global_exit_status != NULL)
		return ;
	trav = lst_of_strings;
	while (trav != NULL)
	{
		new_content = expand_string(lst->content, env);
		if (new_content == NULL)
			return ;	
		free(trav->content);
		trav->content = (void *) new_content;
		trav = trav->next;
	}
}

/** goes through the list of t_ast nodes. For every nodes, checks if the *cmds pointer is not
 * NULL. If it is not NULL, checks for every pointer in the t_cmd_def struct if the pointers to
 * *cmd, *redir and *assign are not NULL. If they are not NULL, calls expand_list to expand the nodes
 * in the list
 **/ 
void	expander(t_list *nodes, t_env *env)
{
	t_list	*traverser;
	t_ast	*current;

	traverser = nodes;
	while (traverser != NULL)
	{
		current = traverser->content;
		if (current->cmds)
		{
			if (current->cmds->cmd)
				expand_list(current->cmds->cmd, env);
			if (current->cmds->redir)
				expand_list(current->cmds->redir, env);
			if (current->cmds->assign)
				expand_list(current->cmds->assign, env);
		}
		if (g_global_exit_status != NULL)
			return ;
		traverser = traverser->next;
	}
}

