/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:17:09 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/07 11:30:54 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_ret(void *ptr, void *ptr2, int ret)
{
	free(ptr);
	ptr = NULL;
	free(ptr2);
	ptr = NULL;
	return (ret);
}
