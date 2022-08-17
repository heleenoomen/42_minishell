/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:26:01 by kanykei           #+#    #+#             */
/*   Updated: 2022/08/17 17:03:38 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "lists/list.h"
# include "../ast.h"

typedef struct s_exec
{
	char		**curr_cmd;
	int			status;
	int			pipe_fd[2];
	int			pid;
	int			fd_in;
	int			fd_out;
	int			builtin;
	int			pipe;
	int			forks;
	t_list		**cmds_list;
	t_cmd_def	*cmd_type;
}	t_exec;

int				main_executor(char *readline, t_minishell *minishell);
int				start_execution(t_list **nodes, t_minishell *minishell);
void			init_exec_struct(t_exec *exec, t_list **cmds_list);
int				execute_commands(t_exec *exec_cmds, t_minishell *minishell);
void			execute_cmds_and_builtins(t_exec *exec_cmds, t_ast **node, t_minishell *minishell);
void			get_tree(t_list **nodes, t_ast *tree, int node_id);



#endif
