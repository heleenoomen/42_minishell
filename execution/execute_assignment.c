/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_assignment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:57:38 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/17 10:17:14 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* heleen: my env functions will do this for you :-) */
//t_assigment	*get_keyvalue_pair(char	*arg)
//{
//	t_assigment	*pair;
//	int			locate_key;
//
//	if (!arg)
//		pair = NULL;
//	else
//	{
//		pair = malloc(sizeof(t_assigment));
//		if (!pair)
//			return (NULL);
//		locate_key = ft_strchr(arg, '=') - arg;
//		pair->value = remove_quotes(&arg[locate_key + 1]);
//		pair->key = ft_substr(arg, 0, locate_key);
//	}
//	return (pair);
//}

int	execute_assignment(t_list *assign_lst, t_minishell *shell)
{
//	t_assigment	*pair;
	int			status;

	status = 0;
	if (!assign_lst)
		return (status);
	while (assign_lst && status == 0)
	{
		status = add_string_to_env(shell->env, assign_lst->content, NO_EXPORT); /* this function will take care of everything :-) */
/*		pair = get_keyvalue_pair((char *)assign_lst->content);
 *			else add it into the env list 
 *			if (!pair->key || !pair->value)
 *				status = 1;
 */ 
		assign_lst = assign_lst->next;
	}
	return (status);
}
