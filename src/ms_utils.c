/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:17:09 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/15 14:41:12 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arg(char **argv)
{
	int	i;

	if (argv == NULL)
		return (-1);
	i = 0;
	while (argv[i] != NULL)
		i++;
	return (i);
}
