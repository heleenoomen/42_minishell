/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:53:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/22 19:39:36 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_builtins(char *builtin_name, char *error)
{
	ft_putstr_fd(builtin_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
}

bool	is_builtin(char *s)
{
	if (ft_strncmp_uplo(s, "echo", 5) && ft_strcmp(s, "cd") && ft_strcmp(s, "pwd")
		&& ft_strcmp(s, "export") && ft_strcmp(s, "unset") && ft_strcmp(s, "env")
		&& ft_strcmp(s, "exit"))
		return (false);
	dprintf(2, "is_builtin, return true\n");
	return (true);
}

void	call_builtin(int argc, char **argv, t_minishell *minishell)
{
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
}

t_list	*get_args(t_exec *exec)
{
	t_ast		*ast;
	t_list		*cmds_list;
	t_cmd_def	*cmds;

	if (exec != NULL && exec->cmds_list != NULL)
	{
		cmds_list = *(exec->cmds_list);
		if (cmds_list != NULL)
		{
			ast = (t_ast *)(cmds_list->content);
			if (ast != NULL)
			{
				cmds = ast->cmds;
				if (cmds != NULL)
				{
					return (cmds->cmd);
				}
			}
		}
	}
	return (NULL)
		// if (exec_cmds && exec_cmds->cmds_list && *(exec_cmds->cmds_list) 
		// && (t_ast *)(*(exec_cmds->cmds_list))->content 
		// && ((t_ast *)(*(exec_cmds->cmds_list))->content)->cmds)
		// args = ((t_ast *)(*(exec_cmds->cmds_list))->content)->cmds->cmd;
}
/* checks if a cmd is a builtin. If so, calls the builtin function to
 * execute the builtin command and returns true. If the command is not
 * a builtin, returns false
 */
bool	builtin(t_exec *exec, t_minishell *minishell, bool single_builtin)
{
	char	*s;
	t_list	*args;
	int		argc;
	char	**argv;
	int		fd_in_cpy;
	int		fd_out_cpy;

	args = get_args(exec);
	if (args == NULL)
		return (false);
	if (!is_builtin(args->content))
		return (false);
	if (single_builtin)
		run_redirecions_single_builtin(exec);
	
	if (single_builtin)
	{
		exec_cmds->cmd_type = ((t_ast *)(*(exec_cmds->cmds_list))->content)->cmds;
		if (execute_redirection(exec_cmds, minishell))
			return (true);
		if (exec_cmds->fd_in > 0)
		{
			fd_in_cpy = dup(STDIN_FILENO);
			dup2(exec_cmds->fd_in, 0);
			close(exec_cmds->fd_in);
		}		
		if (exec_cmds->fd_out > 1)
		{
			fd_out_cpy = dup(STDOUT_FILENO);
			dup2(exec_cmds->fd_out, STDOUT_FILENO);
			close(exec_cmds->fd_out);
		}
	}
	dprintf(2, "still in builtin");
	if (!ft_strcmp(s, "pwd"))
		mini_pwd();
	else if (!ft_strcmp(s, "exit"))
		mini_exit(minishell);
	else
	{
		argv = list_to_argv(args, &argc);
		if (argv == NULL)
			error_builtins(s, ENOMEM);
		else
			call_builtin(argc, argv, minishell);
		free(argv);
	}
	if (single_builtin)
	{
		if (exec_cmds->fd_out > 1)
		{
			close(STDOUT_FILENO);
			dup(fd_out_cpy);
		}
		if (exec_cmds->fd_in > 0)
		{
			close(STDIN_FILENO);
			dup(fd_in_cpy);
		}
	}
	return (true);
}
