/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:46:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/13 16:28:18 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_exit(t_minishell *minishell)
{
	ft_putstr_fd("exit\n", 1);
	free_minishell(minishell);
	exit(g_global_exit_status);
}

