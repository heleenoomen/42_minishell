/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:39:14 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 17:05:00 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_cd_update_env(t_env *env, char *oldpwd, char *newpwd)
{
	if (update_env(env, "OLDPWD", oldpwd, EXPORT) == -1)
		ft_putstr_fd("Warning: Minishell: could not update OLDPWD variable (System\
error)\n", 2);
	if (update_env(env, "PWD", newpwd, EXPORT) == -1)
		ft_putstr_fd("Warning: Minishell: could not update PWD variable (System\
error)\n", 2);
}

void	go_home(t_env *env, char *oldpwd)
{
	char *home;

	home = find_value(env, "HOME");
	if (home == NULL)
		return ;
	if (chdir(home) == -1)
	{
		perror("cd");
		return ;
	}
	mini_cd_update_env(env, oldpwd, home);
	return ;
}

void	mini_cd(int argc, char **argv, t_env *env)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
	{
		write(2, "System error\n", 13);
		return ;
	}
	if (argc == 1)
	{
		go_home(env, oldpwd);
		return ;
	}
	if (chdir(argv[1]) == -1)
	{
		perror(argv[1]);
		return ;
	}
}

