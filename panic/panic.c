/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:57:59 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/20 17:42:59 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	clear_env_data(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		free(env->arr_pairs[i]->key);
		free(env->arr_pairs[i]->value);
		i++;
	}
	free(env->arr_pairs);
}

void	panic(char *message, t_env_data *env)
{
	perror(message);
	clear_env_data(env_data);
	exit(errno);
}

