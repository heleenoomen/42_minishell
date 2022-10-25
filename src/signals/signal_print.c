/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:27:19 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/25 16:51:49 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_print(int status)
{
	if (status == SIGINT)
		write(1, "\n", 1);
	if (status == SIGQUIT)
		write(1, "Quit: 3\n", 9);
	if (status == SIGBUS)
		write(1, "Bus error: 10\n", 15);
	if (status == SIGSEGV)
		write(1, "Segmentation fault: 11\n", 24);
}
