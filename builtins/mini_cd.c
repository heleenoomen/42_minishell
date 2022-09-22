/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:39:14 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/22 17:00:54 by hoomen           ###   ########.fr       */
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

int	set_oldpwd(char **oldpwd)
{
	*oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
	{
		g_global_exit_status = EXIT_ERROR_DEFAULT;
		return (-1);
	}
	return (0);
}

int	check_access(char *path, int *status)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK))
			return (0);
		g_global_exit_status = EACCESS;
		*status = EACCESS;
		return (-1);
	}
	g_global_exit_status = ENOENT;
	*status = ENOENT;
	return (-1);
}

int	go_home(t_env *env, char *oldpwd, int *status)
{
	char *home;

	home = find_value(env, "HOME");
	if (home == NULL)
		return (0);
	if (check_access(home, status))
		return (-1);
	if (chdir(home) == -1)
	{
		g_global_exit_status = EXIT_ERROR_DEFAULT;
		*status = ERROR_PERROR;
		return (-1);
	}
	mini_cd_update_env(env, oldpwd, home);
	return (0);
}

void	mini_cd(int argc, char **argv, t_env *env)
{
	char	*oldpwd;
	int		status;

	if (set_oldpwd(&oldpwd))
		return (error_builtins("cd", SYS_ERR));
	if (argc == 1)
	{
		if (go_home(env, oldpwd, &status))
			return (error_builtins("cd", status));
		return ;
	}
	if (check_access(argv[1], &status))
		return (error_builtins("cd", status));	
	if (chdir(argv[1]) == -1)
	{
		g_global_exit_status = EXIT_ERROR_DEFAULT;
		return (error_builtins("cd", ERROR_PERROR));
	}
	mini_cd_update_env(env, oldpwd, argv[1]);
}

