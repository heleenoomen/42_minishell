/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:34:28 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/12 15:18:56 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_access(char *command, bool *file_exists)
{
	if (access(command, F_OK) == 0)
	{
		*file_exists = 1;
		if (access(commd, X_OK) == 0)
			return (0);
	}
	return (-1);
}

int	extract_all_paths(char ***all_paths, bool *file_exists, t_env *env)
{
	int	i;

	i = 0;
	while (env->envp[i] != NULL)
	{
		if (ft_strncmp(env->envp[i], "PATH=", 5) == 0)
		{
			*all_paths = ft_split(env->envp[i] + 5);
			if (*all_paths == NULL)
				return (NO_MEM);
			return (0);
		}
		i++;
	}
	return (NO_FILE);
}

int	assemble_path(char **path, char *command, char **all_paths, bool *file_exists)
{
	int		i;
	char	*with_slash;

	i = 0;
	while (all_paths[i] != NULL)
	{
		with_slash = ft_strjoin(all_paths[i], "/");
		if (with_slash == NULL)
			return (NO_MEM);
		*path = ft_strjoin(with_slash, command);
		if (*path == NULL)
		{
			free(with_slash);
			return (NO_MEM);
		}
		if (my_access(*path, file_exists) == 0)
			return ;
		free(with_slash);
		free(*path);
		i++;
	}
	*path = NULL;
	return (NO_FILE);
}	

char	*find_path(char *command, t_env *env)
{
	bool	file_exists;
	char	**all_paths;
	char	*path;
	int		i;
	int		ret;

	file_exists = 0;
	ret = extract_all_paths(&all_paths, &file_exists, env);
	if (ret == NO_MEM)
		panic_builtins("System error", env);
	if (ret == NO_FILE)
		panic_file(command, file_exists, env, PA);
	ret = assemble_path(&path, command, all_paths, &file_exists);
	if (ret == NO_MEM)
		panic_builtins("System error", env);
	if (ret == NO_FILE)
		panic_file(command, file_exists, env, EX);
	if (path == NULL)
		panic_builtins("Undefined error", env);
	return (path);
}

