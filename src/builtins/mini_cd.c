/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:39:14 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/13 19:22:08 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_cd_update_env(t_env *env, char *oldpwd, char *newpwd)
{
	if (change_value_existing_key(env, oldpwd, "OLDPWD", UNKNOWN) == -1)
		ft_putstr_fd("Warning: Minishell: could not update OLDPWD variable (System\
error)\n", 2);
	if (change_value_existing_key(env, argv[1], "PWD", UNKNOWN) == -1)
		ft_putstr_fd("Warning: Minishell: could not update PWD variable (System\
error)\n", 2);
}

void	go_home(t_env *env, char *oldpwd)
{
	int		i;

	i = get_key(env, "HOME");
	if (i == -1)
		return ;
	if (chdir(env->env_hash[i].value) == -1)
	{
		perror("cd");
		return ;
	}
	minicd_update_env(env, oldpwd, env_hash[i].value);
	return ;
}

void	mini_cd(int argc, char **argv, t_env *env)
{
	char	*oldpwd;
	int		i;

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

