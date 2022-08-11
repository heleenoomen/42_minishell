/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:57:59 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/11 14:25:27 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	panic_builtins(char *message, t_env *env)
{
	perror(message);
	if (env != NULL)
		clear_env_data(env);
	exit(errno);
}

