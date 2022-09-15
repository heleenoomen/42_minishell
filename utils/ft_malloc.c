/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:23:56 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/15 12:11:26 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc(size_t size, char *message, bool exit, t_minishell *minishell)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
	{
		if (exit)
			exit_minishell(ENOMEM, message, minishell);
		else
		{
			g_global_exit_status = ENOMEM;
			/* print error message? >> NO! */
		}
	}
	return (ret);
}
	
