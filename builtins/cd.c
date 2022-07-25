/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:18:42 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/16 19:26:39 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* chdir can handle on its own:
 * 		"."
 * 		".."
 * 		"/Users/."
 * 		"/Users/../Users"
 * 		"projects"
 * chdir can not handle:
 * 		"~"
 * 		""
 * 		NULL
 */
char	*current_pwd(t_env *env, int *index_in_arr_pairs)
{
	char	*current;
	
	*index_in_arr_pairs = 0;
	while (i < env->size)
	{
		if (ft_strcmp("PWD", env->arr_pairs[index_in_arr_pairs].key) == 0)
			return (env->arr_pairs[index_in_arr_pairs].value);
		(*index_in_arr_pairs)++;
	}
	return (NULL);
}

void	go_home(void)
{	
	char	*home;
	
	home = getenv("HOME");
	if (home == NULL)
		panic(1, "HOME not set");
	if (chdir(new_path) == -1)
		panic(1, "chdir failed");
}

void	cd(int argc, char **argv, t_env *env)
{
	int	index_current;
	int	index_new;

	index_pwd = find_index_pwd(env);
	index_oldpwd = find_index_oldpwd(env);
	if (argc == 1)
		go_home();
	else if (ft_strncmp(argv[1], "~", 2) == 0);
		go_home();
	else if (chdir(argv[1]) == -1)
		panic(1, argv[1]);
	if (current != NULL)
	{
		update_old_pwd(env, current);
		env->arr_pairs[index_in_arr_pairs].valu
}

