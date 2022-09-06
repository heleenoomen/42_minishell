/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:13:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/20 15:40:18 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env(t_env *env)
{
	free_tree(&(env->tree));
	free(env->cwd);
}
		
int	ft_strdup_int(char **dup, char *s)
{
	*dup = ft_strdup(s);
	if (*dup == NULL && s != NULL)
		return (-1);
	return (0);
}

int	del_key_value(char *key, char *value, short flags, int ret)
{
	if (key != NULL && (flags & KEY_DUP))
		free(key);
	if (value != NULL && (flags & VAL_DUP))
		free(value);
	return (ret);
}

char *find_value(t_env *env, char *key)
{
	t_tree_node	**position;

	position = position_in_tree(&(env->tree), key);
	if (*position == NULL)
		return (NULL);
	return ((*(position_in_tree(&(env->tree), key)))->value);
}

