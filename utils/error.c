/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:13:41 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/15 12:07:18 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* two wrappers in case an error occurs and we want to return and set either
 * the status variable or the global variable before returning a NULL pointer
 * (erro_ptr) or before returning from a void function (error_void)
 */
void	*error_ptr(int *status, int error_code)
{
	if (status != NULL)
		*status = error_code;
	else
		g_global_exit_status = error_code;
	return (NULL);
}

void	error_void(int *status, int error_code)
{
	if (status != NULL)
		*status = error_code;
	else
		g_global_exit_status = error_code;
}

