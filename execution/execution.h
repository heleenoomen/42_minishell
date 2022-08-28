/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:26:01 by kanykei           #+#    #+#             */
/*   Updated: 2022/08/28 20:37:04 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../parser/ast.h"
# include <signal.h>

extern int	g_global_exit_status;

typedef struct s_exec
{
	char		**curr_cmd;
	t_list		**cmds_list;
	t_cmd_def	*cmd_type;
	int			status;
	int			pipe_fd[2];
	int			pid;
	int			fd_in;
	int			fd_out;
	int			builtin;
	int			pipe;
	int			forks;
}	t_exec;

int				main_executor(char *readline, t_minishell *minishell);
int				start_execution(t_list **nodes, t_minishell *minishell);
void			init_exec_struct(t_exec *exec, t_list **cmds_list);
int				execute_commands(t_exec *exec_cmds, t_minishell *minishell);
void			execute_cmds_and_builtins(t_exec *exec_cmds, t_ast **node, \
				t_minishell *minishell);
void			get_tree(t_list **nodes, t_ast *tree, int node_id);
void			execute_cmd_block(t_exec *exec_cmds, t_ast *node, \
				t_minishell *minishell);
void			execute_pipe(t_exec *exec);
void			duplicate_fd(t_exec *exec);

/* && and || operators */
int				execute_and_or_cmd(t_exec *exec, t_ast *node);
void			reset_node(t_exec *exec);

/* Redirections  - incopmlete file is missing*/
void			execute_redirect_in(char *file, int	*fd);
void			execute_redirect_overwrite(char *file, int	*fd);
void			execute_redirect_append(char *file, int	*fd);
void			execute_redirect_inout(char *file, int	*fd_in, int *fd_out);
void			execute_redirection(t_exec	*exec, t_minishell *minishell);

/* Run COMMANDS !!! ENV AND PATH NEEDED !!!*/
int				run_cmd_child(t_exec *exec, t_cmd_def *cmd, \
				t_minishell *minishell);
int				child_process(t_exec *exec, t_cmd_def *cmd, \
				t_minishell *minishell);
int				parent_process(t_exec *exec, t_cmd_def *cmd);
int				fork_process(t_exec *exec_cmds, t_cmd_def *cmds, \
				t_minishell *minishell);
/* SIGNALS */
void			parent_send_signal(void);
void			child_send_signal(void);
void			child_sigint(void);
void			child_sigquit(void);
void			parent_sigint(void);
void			parent_sigquit(void);
void			call_process_exit(int signal);
void			send_exit_status(int signal);

#endif