/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_assignment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:57:38 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/25 11:15:25 by kanykei          ###   ########.fr       */
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
		// dprintf(2, "assgin_lst->content = %s\n", assign_lst->content);
		status = update_env_string(shell->env, assign_lst->content, ASSIGN | NO_EXPORT); /* this function will take care of everything :-) */
/*		pair = get_keyvalue_pair((char *)assign_lst->content);
 *			else add it into the env list 
 *			if (!pair->key || !pair->value)
 *				status = 1;
 */ 
		assign_lst = assign_lst->next;
	}
	return (status);
}
