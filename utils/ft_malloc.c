/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:23:56 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/08 19:06:59 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc(size_t size, char *message, bool exit, t_shell *minishell)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
	{
		if (exit)
			exit_minishell(message, MALLOC_ERR, minishell);
		else
		{
			g_global_exit_status = MALLOC_ERR;
			/* print error message? >> NO! */
		}
	return (ret);
}
	
void	*ft_calloc2(size_t size, int *status)
{
	void	*ret;

	ret = ft_malloc(size, status);
	if (ret == NULL)
		return (NULL);
	ft_memset(ret, 0, size);
	return (ret);
}

