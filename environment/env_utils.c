/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:13:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/25 13:42:40 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env(t_env **env_dir)
{
	t_env *env;

	env = *env_dir;
	free_tree(&(env->tree));
	*env_dir = NULL;
	free(env);
	*env_dir = NULL;
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

