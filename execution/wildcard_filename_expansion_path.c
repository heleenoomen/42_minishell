/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_filename_expansion_path.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:04:08 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/25 22:03:40 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_type_file(t_list	*lst)
{
	t_list		*last_file;
	t_expansion	*file;

	last_file = ft_lstlast(lst);
	file = (t_expansion *)last_file->content;
	file->type = type_file;
}

int	init_path_lst(char **path, t_list **list)
{
	t_list		*new_path;
	t_expansion	*file;
	int			i;

	i = 0;
	while(path[i])
	{
		file = init_file(path[i], type_dir);
		if (!file)
			return (0);
		new_path = ft_lstnew(file);
		if (!new_path)
		{
			free_expansion_file(file);
			return (0);
		}
		ft_lstadd_back(list, new_path);
		i++;
	}
	return (1);
}

int	init_root_dir(t_list **list)
{
	t_list		*temp;
	t_expansion	*file;

	file = init_file("/", type_dir);
	if (!file)
		return (0);
	temp = ft_lstnew(file);
	if (!temp)
	{
		free_expansion_file_struct(file);
		return (0);
	}
	ft_lstadd_back(list, temp);
	return (1);
}

void	free_path_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

t_list	*get_path_for_expansion(char *str)
{
	char	**path;
	t_list	*lst;
	int		end;

	lst = NULL;
	if (str[0] == '/')
	{
		if(!init_root_dir(&lst))
			return (NULL);
	}
	path = ft_split(str, '/');
	if (!path)
	{
		ft_lstclear(&lst, &free_expansion_file_struct);
		return (NULL);
	}
	if (!init_path_lst(path, &lst))
	{
		free_path_split(path);
		ft_lstclear(&lst, &free_expansion_file_struct);
		return (NULL);
	}
	free_path_split(path);
	end = ft_strlen(str) - 1;
	if (str[end] != '/')
		update_type_file(lst);
	return (lst);
}
