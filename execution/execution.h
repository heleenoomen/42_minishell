/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:26:01 by kanykei           #+#    #+#             */
/*   Updated: 2022/09/08 19:40:00 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H


extern int	g_global_exit_status;

enum	e_type
{
	FILE,
	DIRECTORY,
};

typedef struct s_expansion
{
	char		*file;
	enum e_type	type;
}	t_expansion;

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

/* Redirection && filename expansion */
char			*remove_quotes(char *str);
void			filename_expansion(t_list **redir_list);
t_list			*expand_star(char *str);
void			merge_to_list(t_list **curr_lst, t_list *new, t_list *prev, t_lst **lst);
void			get_expand_direct(t_list **lst, t_list *path);
t_list			*get_path_for_expansion(char *str);
void			push_to_redirlst(t_list *path, t_list **lst, char *dir);
int				file_cmp(char *search, char	*files);

/* Find path */
char			*find_path(char *command, t_env *env);

/* Convert t_list with cmd + argument into argv for execve */
char			**list_to_argv(t_list *cmd, int *argc);

#endif

