/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:26:01 by kanykei           #+#    #+#             */
/*   Updated: 2022/09/25 17:53:56 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "ms_typedefs.h"

int	g_global_exit_status;

enum	e_type
{
	type_file,
	type_dir
};

typedef struct s_expansion
{
	char		*file;
	enum e_type	type;
}	t_expansion;



int				main_executor(char *readline, t_minishell *minishell);
int				start_execution(t_list **nodes, t_minishell *minishell);
void			init_exec_struct(t_exec *exec, t_list **cmds_list);
int				execute_commands(t_exec *exec_cmds, t_minishell *minishell);
void			execute_cmds_and_builtins(t_exec *exec_cmds, t_ast **node, \
				t_minishell *minishell);
void			get_tree(t_list **nodes, t_ast *tree, int node_id);
int				execute_cmd_block(t_exec *exec_cmds, t_ast *node, \
				t_minishell *minishell);
int				execute_pipe(t_exec *exec);
void			duplicate_fd(t_exec *exec);
int				execute_assignment(t_list *assign_lst, t_minishell *shell);
/* && and || operators */
int				execute_and_or_cmd(t_exec *exec, t_ast *node);
void			reset_node(t_exec *exec);

/* Redirections  - incopmlete file is missing*/
int				execute_redirect_in(char *file, int	*fd);
int				execute_redirect_overwrite(char *file, int	*fd);
int				execute_redirect_append(char *file, int	*fd);
int				execute_redirect_inout(char *file, int	*fd_in, int *fd_out);
int				execute_redirection(t_exec	*exec, t_minishell *minishell);
int				execute_heredoc(char *delim, t_exec *exec, t_minishell *shell);
void			child_process_heredoc(char *delim, int *fd, t_exec *exec, t_minishell *shell);

/* Run COMMANDS !!! ENV AND PATH NEEDED !!!*/
int				run_cmd_child(t_exec *exec, t_cmd_def *cmd, \
				t_minishell *minishell);
int				child_process(t_exec *exec, t_cmd_def *cmd, \
				t_minishell *minishell);
void			parent_process(t_exec *exec, t_cmd_def *cmd);
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
void			merge_to_list(t_list **curr_lst, t_list *new_item, t_list *prev, t_list **lst);
void			get_expand_direct(t_list **lst, t_list *path);
t_list			*get_path_for_expansion(char *str);
char			*get_path(char *dir_path, char *path);
void			push_to_redirlst(t_list *path, t_list **lst, char *dir);
int				file_cmp(char *search, char	*files);
int				dir_type(unsigned char type);
t_expansion		*init_file(char	*file, enum e_type type);
int				init_root_dir(t_list **list);
char			*get_file(t_list *list);
void			add_redirlst(char *curr_dir, t_list *dir_list, t_list **lst);
int				wildcard_expander(t_list **cmds);

/* Find path */
char			*find_path(char *command, t_env *env);

/* Convert t_list with cmd + argument into argv for execve */
char			**list_to_argv(t_list *cmd, int *argc);

#endif

