/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:41:05 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/25 16:18:29 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast_node(t_list **node)
{
	t_ast	*temp_node;
	t_list	*lst_node;

	if (node && *node)
	{
		lst_node = *node;
		while (ft_lstsize(lst_node))
		{
			temp_node = (t_ast *)lst_get_content(&lst_node);
			if (temp_node->cmds)
				free_cmd_defs(&temp_node->cmds);
			free(temp_node);
		}
		*node = NULL;
	}
}

static void	free_ast_recurs(t_ast **node)
{
	if (!(*node))
		return ;
	free_ast_recurs(&(*node)->child);
	free_ast_recurs(&(*node)->next_sibling);
	free_cmd_defs(&(*node)->cmds);
	free(*node);
	*node = NULL;
}

void	free_full_ast(t_ast **ast)
{
	free_ast_recurs(ast);
	*ast = NULL;
}

void	free_cmd_defs(t_cmd_def **cmds)
{
	if (*cmds)
	{
		if ((*cmds)->cmd)
			ft_lstclear(&((*cmds)->cmd), &free);
		if ((*cmds)->redir)
			ft_lstclear(&((*cmds)->redir), &free);
		if ((*cmds)->assign)
			ft_lstclear(&((*cmds)->assign), &free);
		free(*cmds);
		*cmds = NULL;
	}
}

void	free_syntax_table(void (***table)(t_list **, enum e_grammar))
{
	int	col;

	col = 0;
	while (col < NONTERM)
	{
		free((table)[col]);
		col++;
	}
	free(table);
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell)
	{
		free(minishell->line);
		clear_env(&(minishell->env));
		if (minishell->table)
			free_syntax_table(minishell->table);
	}
}

void	heredoc_child_helper_destruction(t_exec *exec_cmds, t_minishell *shell)
{
	free_minishell(shell);
	free_ast_node(exec_cmds->cmds_list);
	free_cmd_defs(&exec_cmds->cmd_type);
	// rl_clear_history();
}

void	heredoc_helper_destruction(char **update, char **line, int *fd, t_exec *exec_cmds)
{
	if (fd)
	{
		close(fd[1]);
		if (exec_cmds->curr_cmd)
			free(exec_cmds->curr_cmd);
		free_cmd_defs(&exec_cmds->cmd_type);
		free_ast_node(exec_cmds->cmds_list);
	}
	free(*line);
	*line = NULL;
	free(*update);
	*update = NULL;
}

void	heredoc_helper_destruction2(char *delim, int status)
{
	if (delim)
		free(delim);
	exit(status);
}

void	free_expansion_file(t_expansion *file)
{
	if (file->file)
		free(file->file);
	file->file = NULL;
	free(file);
}

void	free_expansion_file_struct(void *content)
{
	free_expansion_file((t_expansion *)content);
}
