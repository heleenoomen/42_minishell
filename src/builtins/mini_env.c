/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:29:53 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 17:31:18 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (env->env_hash[i].key != NULL && env->env_hash[i].for_export == true)
		{
			ft_putstr_fd(env->env_hash[i].key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->env_hash[i].value, 1);
			write(1, "\"", 1);
			write(1, "\n", 1);
			i++;
		}
		i++;
	}
}
