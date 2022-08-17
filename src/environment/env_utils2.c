/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:13:39 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 18:39:25 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env(t_env *env)
{
	free_tree(&(env->tree));
	free(env->env_hash);
	free(env->cwd);
}
		
int	ft_strdup_int(char **dup, char *s)
{
	*dup = ft_strdup(s);
	if (*dup == NULL && s != NULL)
		return (-1);
	return (0);
}

int	ft_strjoin_int(char **join, char *s1, char *s2)
{
	*join = ft_strjoin(s1, s2);
	if (*join == NULL)
		return (-1);
	return (0);
}

int	del_key_value(char *key, char *value, short flags, int ret)
{
	if (key != NULL && flags & KEY_DUP)
		free(key);
	if (value != NULL && flags & VAL_DUP)
		free(value);
	return (ret);
}

char *find_value(t_env *env, char *key)
{
	return ((*(position_in_tree(&(env->tree), key)))->value);
}
