/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:23:56 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/06 11:37:13 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc(size_t size, int *status, char *message)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
	{
		*status = ENOMEM;
		if (message != NULL)
			perror("System error");
	}
	return (ret);
}
	
