/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:21:49 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/14 14:24:25 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* returns a pointer to the value for a given key. Returns NULL if the key is
 * not found or if the value is not set
 */
char	*find_value(t_env *env, char *key)
{
	int	i;

	i = key_index(env, key);
	if (i == -1)
		return (NULL)
	return (env->env_hash[i].value);
}
