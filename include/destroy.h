/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:39:41 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/20 16:18:57 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESTROY_H
# define DESTROY_H

# include "ms_typedefs.h"

/*free environment in free_minishell function*/


void	free_minishell(t_minishell *minishell);
void	free_ast_node(t_list **node);
void	free_full_ast(t_ast **ast);
void	free_cmd_defs(t_cmd_def **cmds);
void	free_cmd_defs(t_cmd_def **cmds);
void	heredoc_child_helper_destruction(t_exec *exec_cmds, t_minishell *shell);
void	heredoc_helper_destruction(char **update, char **line, int *fd, t_exec *exec_cmds);
void	heredoc_helper_destruction2(char *delim, int status);
void	free_syntax_table(void (***table)(t_list **, enum e_grammar));
void	free_expansion_file_struct(void *content);
void	free_expansion_file(t_expansion *file);


#endif
