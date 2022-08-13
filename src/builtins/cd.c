/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:37:38 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/13 14:58:24 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		go_home(t_env *env)
{
	int		i;

	i = 0;
	dprintf(2, "in go_home\n");
	while (i < env->size)
	{
		if (ft_strcmp(env->arr_pairs[i].key, "HOME") == 0)
		{
			dprintf(2, "home found\n");
			if (chdir(env->arr_pairs[i].value) == -1)
			{
				dprintf(2, "env->arr_pairs[i].value = %s\n", env->arr_pairs[i].value);
				perror(env->arr_pairs[i].value);
				ms_exit_status = errno;
				return ;
			}
			dprintf(2, "changed directory\n");
			i = update_env(env, "PWD", env->arr_pairs[i].value);
			if (i)
				perror(NULL);
			return ;
		}
		i++;
	}
}
	
void	mini_cd(int argc, char **argv, t_env *env)
{
	int		i;
	char	*cwd;
	
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror(argv[1]);
		ms_exit_status = errno;
		return ;
	}
	if (argc == 1)
	{
		go_home(env);
		return ;
	}
	else if (chdir((const char *)argv[1]) == -1)
	{
		perror(argv[1]);
		ms_exit_status = errno;
		return ;
	}
	i = update_env(env, argv[1], "PWD");
	if (i)
		perror(argv[i]);
	return ;
}

