/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:53:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/25 16:15:01 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *s)
{
	if (s == NULL)
		return (false);
	if (ft_strncmp_uplo(s, "echo", 5) && ft_strcmp(s, "cd") && ft_strcmp(s, "pwd")
		&& ft_strcmp(s, "export") && ft_strcmp(s, "unset") && ft_strcmp(s, "env")
		&& ft_strcmp(s, "exit"))
		return (false);
	return (true);
}

void	call_builtin(t_ast *node, char *cmd, t_minishell *minishell)
{
	char	**argv;
	int		argc;

	argv = list_to_argv(node->cmds->cmd, &argc);
	if (argv == NULL)
		return (error_builtins(cmd, NULL, ENOMEM));
	if (argv[0] == NULL)
		return (error_builtins(cmd, NULL, ERROR_UNDEFINED));
	if (ft_strncmp_uplo(argv[0], "echo", 5) == 0)
		mini_echo(argc, argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		mini_cd(argc, argv, minishell->env);
	else if (ft_strcmp(argv[0], "export") == 0)
		mini_export(argc, argv, minishell->env);
	else if (ft_strcmp(argv[0], "unset") == 0)
		mini_unset(argc, argv, minishell->env);
	else if (ft_strcmp(argv[0], "env") == 0)
		mini_env(minishell->env);
	else if (!ft_strcmp(argv[0], "exit"))
		mini_exit(argc, argv, minishell);
}

t_ast	*get_ast_node(t_exec *exec)
{
	t_list		*cmds_list;

	if (exec != NULL && exec->cmds_list != NULL)
	{
		cmds_list = *(exec->cmds_list);
		if (cmds_list != NULL)
			return ((t_ast *)(cmds_list->content));
	}
	return (NULL);
}

int	run_redirections_single_builtin(t_exec *exec, t_ast *node, int fd_cpys[2], t_minishell *minishell)
{
	exec->cmd_type = node->cmds;
	if (execute_redirection(exec, minishell))
		return (-1);
	printf("after execute_redirection\n");
	printf("exec->fd_out = %d\n", exec->fd_out);
	if (exec->fd_in > 0)
	{
		fd_cpys[0] = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		dup(exec->fd_in);
	}		
	if (exec->fd_out > 1)
	{
		fd_cpys[1] = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
		dup(exec->fd_out);
	}
	return (0);
}

void	restore_stdin_stdout(t_exec *exec, int fd_cpys[2])
{
	if (exec->fd_in > 0)
	{
		close(STDIN_FILENO);
		dup(fd_cpys[0]);
	}
	if (exec->fd_out > 1)
	{
		close(STDOUT_FILENO);
		dup(fd_cpys[1]);
	}
	exec->cmd_type = NULL;

}
/* checks if a cmd is a builtin. If so, calls the builtin function to
 * execute the builtin command and returns true. If the command is not
 * a builtin, returns false
 */
bool	builtin(t_exec *exec, t_minishell *minishell, bool single_builtin)
{
	t_ast	*node;
	int		fd_cpys[2];
	char	*cmd;

	if (single_builtin)
		g_global_exit_status = 0;
	node = get_ast_node(exec);
	if (node == NULL || node->cmds == NULL || node->cmds->cmd == NULL)
		return (false);
	cmd = node->cmds->cmd->content;
	if (!is_builtin(cmd))
		return (false);
	if (single_builtin && run_redirections_single_builtin(exec, node, fd_cpys, minishell))
		return (true);
	if (!ft_strcmp(cmd, "pwd"))
		mini_pwd();
	else
		call_builtin(node, cmd, minishell);
	if (single_builtin)
		restore_stdin_stdout(exec, fd_cpys);
	free(*(exec->cmds_list));
	free_cmd_defs(&node->cmds);
	free(node);
	return (true);
}
