/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:53:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/22 17:19:53 by hoomen           ###   ########.fr       */
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
/* checks if a cmd is a builtin. If so, calls the builtin function to
 * execute the builtin command and returns true. If the command is not
 * a builtin, returns false
 */
bool	builtin(t_exec *exec_cmds, t_minishell *minishell, bool single_builtin)
{
	char	*s;
	t_list	*args;
	int		argc;
	char	**argv;

	(void)exec_cmds;
	single_builtin = !single_builtin;
	args = ((t_ast *)(*(exec_cmds->cmds_list))->content)->cmds->cmd;
	s = args->content;
	dprintf(2, "builtin, s = %s\n", s);
	if (!is_builtin(s))
		return (false);
	//if (single_builtin && execute_redirection(exec_cmds, minishell))
	//	return (true);
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
	return (true);
}
