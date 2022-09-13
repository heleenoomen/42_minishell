/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:36:04 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/13 16:47:26 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(int flag, char *what_failed, t_minishell *minishell)
{
	if (phase == INIT_ENV)
	{
		free_env(minishell->env);
		ft_putstr_fd("Unable to initialize minishell: ", 2);
		ft_putstr_fd(what_failed, 2);
		ft_putstr_fd(" failed.", 2);
		exit(EXIT_FAILURE);
	}
}
	
