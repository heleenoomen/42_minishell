/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_from_env2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:51:19 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 13:05:47 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_from_env(t_env *env, char *key)
{
	int	i;

	del_tree_node(&(env->tree), NULL, key, 0);
	env->deleted++;
	if (env->deleted > 255)
	   shrink_env_hash(env);
}	
