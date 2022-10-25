/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:13:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/25 16:50:45 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* duplicates a string using ft_strdup. On succes, returns 0. If malloc fails,
 * returns -1. */
int	ft_strdup_int(char **dup, char *s)
{
	*dup = ft_strdup(s);
	if (*dup == NULL && s != NULL)
		return (-1);
	return (0);
}
