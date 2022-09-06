/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:53:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/06 10:18:26 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* checks if a cmd is a builtin. If so, calls the builtin function to
 * execute the builtin command and returns true. If the command is not
 * a builtin, returns false
 */
int	builtin(t_list *cmd, t_minishell *minishell)
{
	int		argc;
	char	**argv;

	argv = list_to_argv(cmd, &argc);
	if (ft_strncmp_uplo(argv[0], "echo", 5) == 0)
		mini_echo(argc, argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		mini_cd(argc, argv, minishell->env);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		mini_pwd();
	else if (ft_strcmp(argv[0], "export") == 0)
		mini_export(argc, argv, minishell->env);
	else if (ft_strcmp(argv[0], "unset") == 0)
		mini_unset(argc, argv, minishell->env);
	else if (ft_strcmp(argv[0], "env") == 0)
		mini_env(minishell->env);
	else if (ft_strcmp(argv[0], "exit") == 0)
		mini_exit(minishell->env);
	else
		return (false);
	return (true);
}
				
