/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_assignment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:57:38 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/06 09:42:33 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*remove_quotes(char *str)
{
	char	*removed;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (str[0] == '\'' || str[0] == '\"')
		removed = ft_substr(str, 1, len - 2);
	else
		removed = ft_strdup(str);
	return (removed);
}

t_assigment	*get_keyvalue_pair(char	*arg)
{
	t_assigment	*pair;
	int			locate_key;

	if (!arg)
		pair = NULL;
	else
	{
		pair = malloc(sizeof(t_assigment));
		if (!pair)
			return (NULL);
		locate_key = ft_strchr(arg, '=') - arg;
		pair->value = remove_quotes(&arg[locate_key + 1]);
		pair->key = ft_substr(arg, 0, locate_key);
	}
	return (pair);
}

int	execute_assignment(t_list *assign_lst, t_minishell *shell)
{
	t_assigment	*pair;
	int			status;

	status = 0;
	if (!assign_lst)
		return (status);
	while (assign_lst && status == 0)
	{
		pair = get_keyvalue_pair((char *)assign_lst->content);
			/* if key exists in the environment -> update the value;
			else add it into the env list */
			if (!pair->key || !pair->value)
				status = 1;
		assign_lst = assign_lst->next;
	}
	if (status == 1)
		/* free assignment pair list */
	return (status);
}
