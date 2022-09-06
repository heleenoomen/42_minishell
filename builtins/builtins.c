/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:53:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/19 13:56:20 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(char **argv, t_env *env)
{
	int	argc;

	argc = get_argc(argv);
	if (ft_strncmp_uplo(argv[0], "echo", 5) == 0)
		mini_echo(argc, argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		mini_cd(argc, argv, env);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		mini_pwd();
	else if (ft_strcmp(argv[0], "export") == 0)
		mini_export(argc, argv, env);
	else if (ft_strcmp(argv[0], "unset") == 0)
		mini_unset(argc, argv, env);
	else if (ft_strcmp(argv[0], "env") == 0)
		mini_env(env);
	else if (ft_strcmp(argv[0], "exit") == 0)
		mini_exit(env);
	else
		return (0);
	return (1);
}
				
