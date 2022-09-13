/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:39:41 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/13 16:41:14 by hoomen           ###   ########.fr       */
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


#endif
