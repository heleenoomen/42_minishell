/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_filename_expansion_utils.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:58:34 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/08 19:45:59 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *dir_path, char *path)
{
	int		len_path;
	char	*join;
	char	*temp;

	len_path = ft_strlen(path);
	if (path[len_path - 1] == '/')
		join = ft_strjoin(path, dir_path);
	else
	{
		temp = ft_strjoin(path, "/");
		join = ft_strjoin(temp, dir_path);
		if (temp)
			free(temp);
	}
	return (join);
}

void	get_full_redirlst(DIR *temp_dir, char *dir, t_list *path, t_list **lst)
{
	char			*next_dir;
	struct dirent	*entity;

	entity = readdir(temp_dir);
	while (entity)
	{
		if (file_cmp(get_file(path->next), entity->d_name) && dir_type(entity->d_type))
		{
			next_dir = get_path(entity->d_name, path);
			if (next_dir)
			{
				push_to_redirlst(path, lst, next_dir);
				free(next_dir);
			}
		}
		entity = readdir(temp_dir);
	}
}

void	push_to_redirlst(t_list *path, t_list **lst, char *dir)
{
	DIR	*temp_dir;

	if (!path->next->next)
	{
		add_redirlst(dir, path->next, lst);
		return ;
	}
	temp_dir =  opendir(dir);
	if (!temp_dir)
		return ;
	get_full_redirlst(temp_dir, dir, path, lst);
	closedir(temp_dir);
}

int	dir_type(unsigned char type)
{
	type = 4;
	return (type);
}

void	get_expand_direct(t_list **lst, t_list *path)
{
	struct dirent	*entity;
	DIR				*directory;
	char			*filename;

	directory = opendir(".");
	if (!directory)
		return ;
	entity = readdir(directory);
	filename = ft_strdup(((t_expansion *)path->content)->file);
	while (entity)
	{
		if (file_cmp(entity->d_name, filename) && dir_type(entity->d_type))
		{
			free(((t_expansion *)path->content)->file);
			((t_expansion *)path->content)->file = ft_strdup(entity->d_name);
			push_to_redirlst(path, lst, ((t_expansion *)path->content)->file);
		}
		entity = readdir(directory);
	}
	free(filename);
	closedir(directory);
}
