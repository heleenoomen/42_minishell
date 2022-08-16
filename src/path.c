/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:34:28 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/14 19:00:10 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_access(char *command, bool *file_exists)
{
	if (access(command, F_OK) == 0)
	{
		*file_exists = 1;
		if (access(command, X_OK) == 0)
			return (0);
	}
	return (-1);
}

int	extract_all_paths(char ***all_paths, t_env *env)
{
	char	*paths_value;

	paths_value = find_value(env, "PATH");
	if (paths_value == NULL)
		return (NO_FILE);
	*all_paths = ft_split(paths_value, ':');
	if (*all_paths == NULL)
		return (NO_MEM);
	return (0);
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
		free(with_slash);
		if (*path == NULL)
			return (NO_MEM);
		if (my_access(*path, file_exists) == 0)
			return (0);
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
	int		ret;

	file_exists = 0;
	ret = extract_all_paths(&all_paths, env);
	if (ret == NO_MEM)
		panic("System error", env);
	if (ret == NO_FILE)
		panic_file(command, file_exists, env, PA);
	ret = assemble_path(&path, command, all_paths, &file_exists);
	if (ret == NO_MEM)
		panic("System error", env);
	if (ret == NO_FILE)
		panic_file(command, file_exists, env, EX);
	if (path == NULL)
		panic("Undefined error", env);
	return (path);
}

