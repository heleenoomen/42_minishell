/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_assignment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 22:57:38 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/25 16:36:46 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_assignment(t_list *assign_lst, t_minishell *shell)
{
	int			status;

	status = 0;
	if (!assign_lst)
		return (status);
	while (assign_lst && status == 0)
	{
		status = update_env_string(shell->env, assign_lst->content, \
			ASSIGN | NO_EXPORT);
		assign_lst = assign_lst->next;
	}
	return (status);
}
