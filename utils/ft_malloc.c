/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:23:56 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/06 15:30:46 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc(size_t size, int *status)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
	{
		if (status == NULL)
			g_global_exit_status = NULL;
		else
			*status = ENOMEM;
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
