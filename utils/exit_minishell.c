/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:36:04 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/15 12:33:13 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(int flag, char *what_failed, t_minishell *minishell)
{
	if (flag == INIT_ENV)
	{
		clear_env(&(minishell->env));
		ft_putstr_fd("Unable to initialize minishell: ", 2);
		ft_putstr_fd(what_failed, 2);
		ft_putstr_fd(" failed.", 2);
		exit(EXIT_FAILURE);
	}
}
	
