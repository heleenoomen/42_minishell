/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:29:53 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/15 11:36:57 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (env->env_hash[i].for_export == true)
		{
			write(1, env->envp[i], ft_strlen(env->envp[i]));
			write(1, "\n", 1);
			i++;
		}
	}
}
