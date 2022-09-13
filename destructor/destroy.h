/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:39:41 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/13 11:34:07 by kanykei          ###   ########.fr       */
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
