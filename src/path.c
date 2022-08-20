/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:34:28 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/20 16:14:51 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_access(char *command, short *flags)
{
	if (access(command, F_OK) == 0)
	{
		(*flags) |=  EXIST;
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

int	assemble_path(char **path, char *command, char **all_paths, short *flags)
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
		if (my_access(*path, flags) == 0)
			return (0);
		free(*path);
		i++;
	}
	*path = NULL;
	return (NO_FILE);
}	

char	*find_path(char *command, t_env *env, bool *parent)
{
	short	flags;
	char	**all_paths;
	char	*path;
	int		ret;

	flags = 0;

	ret = extract_all_paths(&all_paths, env);
	if (ret == NO_MEM)
		return (panic_cp_null("System error", env, parent));
	if (ret == NO_FILE)
		return (panic_file_null(command, env, flags | NOPA, parent));
	ret = assemble_path(&path, command, all_paths, &flags);
	if (ret != 0 && my_access(command, &flags) == 0)
		return (command);
	if (ret == NO_MEM)
		return (panic_cp_null("System error", env, parent));
	if (ret == NO_FILE)
		return (panic_file_null(command, env, flags | ISEXEC, parent)); 
	if (path == NULL)
		return (panic_cp_null("Undefined error", env, parent));
	return (path);
}

