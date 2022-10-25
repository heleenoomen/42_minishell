/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freestrarr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:00:28 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/14 13:05:11 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* frees a null terminated  array of strings (passed by reference) and sets the 
 * pointer to the array to NULL
 */
void	ft_freestrarr(char ***strarr)
{
	int		i;
	char	**ptr;

	if (*strarr == NULL)
		return ;
	ptr = *strarr;
	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	*strarr = NULL;
}

