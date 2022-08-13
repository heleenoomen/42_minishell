/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_uplo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:14:00 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/05 21:49:32 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

/*
// case insensitive strncmp
*/
int	ft_strncmp_uplo(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
		{
			if (!ft_isalpha(s1[i]))
				return ((unsigned char) s1[i] - (unsigned char) s2[i]);
			if (s1[i] + 32 != s2[i] && s1[i] - 32 != s2[i])
				return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		}
		i++;
	}
	return (0);
}
