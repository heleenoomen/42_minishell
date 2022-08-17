/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:17:09 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 18:54:13 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_argc(char **argv)
{
	int	i;

	if (argv == NULL)
		return (-1);
	i = 0;
	while (argv[i] != NULL)
		i++;
	return (i);
}

int	free_ret(void *ptr, void *ptr2, int ret)
{
	free(ptr);
	ptr = NULL;
	free(ptr2);
	ptr = NULL;
	return (ret);
}
