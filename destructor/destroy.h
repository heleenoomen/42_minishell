/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:39:41 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/12 16:24:12 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESTROY_H
# define DESTROY_H

# include "../include/minishell.h"

/*free environment in free_minishell function*/


void	free_minishell(t_minishell *minishell);
void	free_ast_node(t_list **node);
void	free_full_ast(t_ast **ast);
void	free_cmd_defs(t_cmd_def **cmds);
void	free_cmd_defs(t_cmd_def **cmds);

#endif
