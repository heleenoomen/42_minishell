/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:39:14 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/17 11:31:38 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_cd_update_env(t_env *env, char *oldpwd, char *newpwd)
{
	if (update_env(env, "OLDPWD", oldpwd, EXPORT) == -1)
		ft_putstr_fd(WARNING_OLDPWD, 2);
	if (update_env(env, "PWD", newpwd, EXPORT | VAL_DUP) == -1)
		ft_putstr_fd(WARNING_PWD, 2);
}

void	go_home(t_env *env, char *oldpwd)
{
	char *home;

	home = find_value(env, "HOME");
	if (home == NULL)
		return ;
	if (chdir(home) == -1)
		return (error_builtins("cd", ERROR_PERROR));
	mini_cd_update_env(env, oldpwd, home);
}

void	mini_cd(t_list *cmd, t_env *env)
{
	char	*oldpwd;
	int		argc;
	char	**argv;

	argv = list_to_argv(cmd, &argc);
	if (argv == NULL)
		return (error_builtins("cd", ERROR_PERROR));
	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
	{
		g_global_exit_status = SYS_ERR;
		return (error_builtins("cd", ERROR_PERROR));
	}
	if (argc == 1)
	{
		go_home(env, oldpwd);
		return ;
	}
	if (chdir(argv[1]) == -1)
	{
		g_global_exit_status = SYS_ERR;
		return (error_builtins("cd", ERROR_PERROR));
	}
	mini_cd_update_env(env, oldpwd, argv[1]);
	free(argv);
}

