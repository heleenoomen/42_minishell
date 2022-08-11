/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:29:53 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/11 16:31:11 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->envp[i] != NULL)
	{
		write(1, env->envp[i], ft_strlen(env->envp[i]));
		write(1, "\n", 1);
		i++;
	}
}
