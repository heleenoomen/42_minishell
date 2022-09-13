/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_filename_expansion_path.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:04:08 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/08 19:45:59 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_type_file(t_list	*lst)
{
	t_list		*last_file;
	t_expansion	*file;

	last_file = ft_lstlast(list);
	file = (t_expansion *)last_file->content;
	file->type = FILE;
}

int	init_path_lst(char **path, t_list **list)
{
	t_list		*new_path;
	t_expansion	*file;
	int			i;

	i = 0;
	while(path[i] != '\0')
	{
		file = init_file(path[i], DIRECTORY);
		if (!file)
			return (-1);
		new_path = ft_lstnew(file);
		if (!new_path)
		{
			free_expansion_file(file);
			return (-1);
		}
		ft_lstadd_back(list, new_path);
		i++;
	}
	return (0);
}

t_list	*get_path_for_expansion(char *str)
{
	char	**path;
	t_list	*lst;
	int		end;

	if (str[0] == '/')
		if(/*root*/)
			return (NULL);
	path = ft_split(str, '/');
	if (!path)
	{
		ft_lstclear(&lst);
		return (NULL);
	}
	if (init_path_lst(path, &lst) != 0)
	{
		/*free whole path */
		ft_lstclear(&lst, &delete_lst_content);
		return (NULL);
	}
	/*free whole path */
	end = ft_strlen(str) - 1;
	if (str[end] != '/')
		update_type_file(lst);
	return (lst);
}
